/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "MKL25Z4.h"
#include "memory.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <string.h>
#include "mcg.h"

char p[10]="HELLOWORLD";
volatile uint32_t count = 0;
char destination[10];

void uart_init()
{
    __disable_irq();
	//Sets gate clock  for PORTA
	SIM_SCGC5 |= SIM_SCGC5_PORTA_MASK;

	//Enables clock for UART0; source as MCGCLKFLL
	SIM_SCGC4 |= SIM_SCGC4_UART0_MASK;
	SIM_SOPT2 |= SIM_SOPT2_UART0SRC(1);

	// Sets for UART0 mode
	PORTA_PCR1 = PORT_PCR_MUX(2);
	PORTA_PCR2 = PORT_PCR_MUX(2);

	// Disables tx and rx before editing registers
	UART0_C2=0x00;
	UART0_C1=0x00;

    /* Calculate baud_divisor for sbr register and set baud rate */
	UART0_BDH |= 0x00;//(baud_divisor >> 8) & UART0_BDH_SBR_MASK;
	UART0_BDL |= 0x17;//(baud_divisor & UART0_BDL_SBR_MASK);

	UART_C2_REG(UART0_BASE_PTR) |= (UART_C2_TE_MASK | UART_C2_RE_MASK );

	__enable_irq();
}




void print_character(int c)
	{
		while(!(UART0->S1 & UART_S1_TDRE_MASK));
		 UART0->D = c;
	}


void start_timer()
{
	// PLL clock select
	SIM_SOPT2 |= SIM_SOPT2_PLLFLLSEL_MASK;
	SIM_SOPT2 &= ~(SIM_SOPT2_TPMSRC_MASK);

	// Select MCGPLLCLK/2
	SIM_SOPT2 |= SIM_SOPT2_TPMSRC(1);

	// Enable TPM clock
	SIM_SCGC6 |= SIM_SCGC6_TPM0_MASK;

	//Nullify the control registers to ensure counter is not running

	TPM0_SC = 0;
	TPM0_CONF = 0;

	//Set prescalar to 1 when counter is disabled
	TPM0_SC = TPM_SC_PS(0);

	// Setting modulo value to set 10us as the execution timer
	TPM0_MOD = 480;

	//Enable Interrupts for the Timer Overflow
		TPM0_SC |= TPM_SC_TOIE_MASK;
	//Enable the TPM Counter
	TPM0_SC |= TPM_SC_CMOD(1);

	//NVIC_ClearPendingIRQ(TPM0_IRQn);
	NVIC_EnableIRQ(TPM0_IRQn);


}

void stop_timer()
{
	NVIC_DisableIRQ(TPM0_IRQn);//Disable the interrupt
	TPM0_SC = 0;
	TPM0_CONF = 0;
}

void TPM0_IRQHandler()
{
	if(TPM0_SC & TPM_SC_TOF_MASK)
	{
		count++;//incrementing counter to note the number of overflows
		TPM0_SC |= TPM_SC_TOF_MASK;//clearing the overflow mask
	}
}


void Setup_DMA()
{
	SIM_SCGC6 |=0x2;
	SIM_SCGC7 |=0x100;

	DMAMUX0_CHCFG0 |=0x80;

	DMA_SAR0 =p;
	DMA_DAR0 =destination;

	DMA_DSR_BCR0  |= DMA_DSR_BCR_BCR(10);

	DMA_DCR0 |= (DMA_DCR_SSIZE(1) | DMA_DCR_DSIZE(1));
	DMA_DCR0 |= (DMA_DCR_SINC(1) | DMA_DCR_DINC(1));
}

int main(void)
{
		uint32_t x;
		double y;
        Setup_DMA();
        pll_init(8000000, LOW_POWER, CRYSTAL,4,24,MCGOUT);
       start_timer();
        DMA_DCR0 |= DMA_DCR_START(1);
        while(!(DMA_DSR_BCR0 & DMA_DSR_BCR_DONE_MASK));
		stop_timer();

		x = count*480 + TPM0_CNT;
		y = (x / 48000000.00);

		print_character(y);
		int j;
	/* Never leave main */
    return 0;
}
