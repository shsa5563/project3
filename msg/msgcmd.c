/*
 * msgcmd.c
 */

#include "MKL25Z4.h"
#include<stdio.h>
#include <math.h>
#include <string.h>
#include"msgcmd.h"
#include "led.h"


int flag=0;
int flag1=0;
uint8_t arr[10];
uint8_t array1[15]="Checksum error";

 int counter=0;
int counter1=0;
CI_Msg new;

int Brightness=900;

void delay()
{
	int i;
	for(i=0;i<65535;i++);
	for(i=0;i<65535;i++);
}

void uart_init()
{
	uint16_t baud_divisor;

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


	//UART_C2_REG(UART0_BASE_PTR) |= UART_C2_TIE_MASK;//Setup receiver interrupt
	UART_C2_REG(UART0_BASE_PTR) |= UART_C2_RIE_MASK;
	UART_C2_REG(UART0_BASE_PTR) |= (UART_C2_RE_MASK );

	__enable_irq();

	//Enabling NVIC and CPU interrupts
	NVIC_EnableIRQ(UART0_IRQn);
	//Switch on transmitter and receiver
}

void structure_init(CI_Msg *msg){

	msg->command=arr[0]-48;
	msg->length = arr[1]-48;
	msg->data = arr[2]-48;
	msg->checksum =arr[3]-48;
	if(((msg->command)+(msg->length)+(msg->data))!=msg->checksum)
	{
		flag1=1;
		counter1=0;
		counter=0;
		UART_C2_REG(UART0_BASE_PTR) |= (UART_C2_TE_MASK );
		UART_C2_REG(UART0_BASE_PTR) |= UART_C2_TIE_MASK;


	}
	else{
	Decode_CI_Msg(&new);
	counter=0;
	}
	UART_C2_REG(UART0_BASE_PTR) |= UART_C2_RIE_MASK;

}

void Decode_CI_Msg(CI_Msg * msg)
{
	switch(msg->data)
	{
	case LED_RED: Set_White_LED();
		break;
	case LED_BLUE:Set_CYAN_LED();
		break;
	case LED_GREEN:Set_MAGENTA_LED();
		break;
	case LED_DANCE:Set_LED_Dance();
		break;
	}
}
void Set_White_LED()
{
	 	    Intensty_Modify(WHITE, Brightness);
}


void Set_CYAN_LED()
{	    Intensty_Modify(CYAN, Brightness);
}

void Set_MAGENTA_LED()
{	    Intensty_Modify(MAGENTA, Brightness);
}
void Set_LED_Dance()
{
		while(UART0_D!='s')
		{
			Set_WHITE_LED();
			delay();
			Set_CYAN_LED();
			delay();
			Set_MAGENTA_LED();
			delay();
		}
}


void UART0_IRQHandler()
{
	__disable_irq();
	uint8_t status;
	char received;
	status = UART0_S1;
	if(status & UART_S1_RDRF_MASK)
	{
		received= UART0_D;
		if(received!='\r')
		{
			*(arr+counter)= received;
			counter++;
		}
		else
		{
			UART_C2_REG(UART0_BASE_PTR) &= ~(UART_C2_RIE_MASK);
			flag=1;
			received=UART0_D;
		}
	}
	if((status & UART_S1_TDRE_MASK) && (flag1==1))
	{
		if((*(array1+counter1))!='\0')
		{
			UART0_D = *(array1 + counter1);
			counter1++;
		}
		else
		{
			UART_C2_REG(UART0_BASE_PTR) &= ~(UART_C2_TE_MASK);
			UART_C2_REG(UART0_BASE_PTR) &= ~(UART_C2_TIE_MASK);
			flag1=0;
		}
	}
	__enable_irq();
}

int main()
{
	Initialize_LED();
	uart_init();
	int m;
	while(1)
	{
		if(flag==1)
		{
			structure_init(&new);
			flag=0;
		}
	}
	return 0;
}
