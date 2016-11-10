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
#include "spi0.h"
#include "nrf.h"
#include "uart.h"
int main(void)
{
	uint8_t ch[4] ={0};
	UART0_init();
	spi0_init();
    		  nrf_config_write(); //Write config to set as RX
    		  nrf_config_read(); //Read the values to verify
    		  nrf_en_rxaddr_write(); //Write to the En_rxaddr register to activate datapipe 0
    		  nrf_en_rxaddr_read(); //Read the values to verify
    		  nrf_rx_pipesize_write(); //set the pipe size
    		  nrf_rx_pipesize_read(); //Read the values to verify
    		  nrf_rx_addr_write(); //write and set the rx address
    		  nrf_rx_addr_read(); //Read the values to verify
//    		  while(1)
//    		{
//    			  GPIOE_PSOR=1<<0; //toggle CE
//    			  delay(200);
//    			  nrf_read_data(); //poll for data
//    			  GPIOE_PCOR=1<<0;  //toggle CE
//    	  }



//	for(int i=0;i<4;i++){
//		TEST_LOW;
//		spi_send_byte(i+2); //WAITS UNTIL THE TX EMPTY BUFFER FLAG GOES HIGH
//		TEST_HIGH;
//		//for(int j =0; j<100; j++);
//		TEST_LOW;
//	    ch[i] = spi_receive_byte();//  SPI_RD_WR_REG = i+5; //OUTPUT A1 ON SPI
//	    TEST_HIGH;
//	}
//	while(1)
//	{
//	nrf_config_write();
//	nrf_config_read();
//    /* Never leave main */
//	}
    return 0;
}
////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
