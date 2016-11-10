/*
 * led.c
 *
 *  Created on: 09-Oct-2016
 *      Author: Satyanarayana
 */
/*
 * spi0.c
 *
 *  Created on: 04-Nov-2016
 *      Author: Satyanarayana
 */


#include "MKL25Z4.h"
#include <math.h>
#include "led.h"


Colour_LED Colour=OFF;
uint16_t  value=100;

void Initialize_LED()
{
    SIM_BASE_PTR->SCGC6 |= SIM_SCGC6_TPM2_MASK;
	SIM_BASE_PTR->SCGC6 |= SIM_SCGC6_TPM0_MASK;
    SIM_BASE_PTR->SOPT2 |= SIM_SOPT2_TPMSRC(1);

    TPM2_BASE_PTR->SC = TPM_SC_CMOD(1) | TPM_SC_PS(7);
    TPM2_BASE_PTR->MOD = 1875;
    TPM0_BASE_PTR->SC = TPM_SC_CMOD(1) | TPM_SC_PS(7);
    TPM0_BASE_PTR->MOD = 1875;

    SIM_BASE_PTR->SCGC5 |=  0x400;
    SIM_BASE_PTR->SCGC5 |= 0x1000;
    PORTB_BASE_PTR->PCR[18] = PORTB_BASE_PTR->PCR[19] = PORT_PCR_MUX(3);
    PORTD_BASE_PTR->PCR[1]=PORT_PCR_MUX(4);

      TPM2_BASE_PTR->CONTROLS[0].CnSC =  0x20 | 0x4;
      TPM2_BASE_PTR->CONTROLS[1].CnSC =  0x20 | 0x4; ;
      TPM0_BASE_PTR->CONTROLS[1].CnSC =  0x20 | 0x4; ;
}

void Change_LEDColor(uint8_t Character)
{
      if(Character=='w' && value<1000)
      {
    	  value+=100;

      }
      else if(Character=='s' && value>0)
       {
             value-=100;
        }

      else if(Character=='a')
            {
    	  Colour++;
          	 if(Colour>=8)
          	 {
          		Colour=0;
          	 }

            }
      else if(Character=='d')
             {
    	  Colour--;
               if(Colour<=0)
                {
            	   Colour=7;
                }
              }
      Intensty_Modify(Colour, value);

}

Intensty_Modify(Colour_LED Colour, uint16_t Brightness)
{
 if(Colour==RED)
    {
	TPM2_BASE_PTR->CONTROLS[0].CnV = Brightness;
	TPM2_BASE_PTR->CONTROLS[1].CnV = 0;
	TPM0_BASE_PTR->CONTROLS[1].CnV = 0;
	}
	else if(Colour==YELLOW)
	{
	TPM2_BASE_PTR->CONTROLS[0].CnV = TPM2_BASE_PTR->CONTROLS[1].CnV = Brightness;
	TPM0_BASE_PTR->CONTROLS[1].CnV = 0;
	}
	else if(Colour==GREEN)
	{
	TPM2_BASE_PTR->CONTROLS[1].CnV = Brightness;
	TPM2_BASE_PTR->CONTROLS[0].CnV = 0;
	TPM0_BASE_PTR->CONTROLS[1].CnV = 0;
	}
	else if(Colour==BLUE)
	{
	TPM0_BASE_PTR->CONTROLS[1].CnV = Brightness;
	TPM2_BASE_PTR->CONTROLS[1].CnV = 0;
	TPM2_BASE_PTR->CONTROLS[0].CnV = 0;
	}
	else if(Colour==MAGENTA)
	{
	TPM2_BASE_PTR->CONTROLS[0].CnV = TPM0_BASE_PTR->CONTROLS[1].CnV = Brightness;
	TPM2_BASE_PTR->CONTROLS[1].CnV = 0;
	}
	else if(Colour==CYAN)
	{
	TPM2_BASE_PTR->CONTROLS[1].CnV = TPM0_BASE_PTR->CONTROLS[1].CnV = Brightness;
	TPM2_BASE_PTR->CONTROLS[0].CnV = 0;
	}
	else if(Colour==WHITE)
	{
	TPM2_BASE_PTR->CONTROLS[1].CnV = TPM2_BASE_PTR->CONTROLS[0].CnV=TPM0_BASE_PTR->CONTROLS[1].CnV = Brightness;
	}
	else
	{
		TPM2_BASE_PTR->CONTROLS[0].CnV = 0;
		TPM2_BASE_PTR->CONTROLS[0].CnV = 0;
		TPM0_BASE_PTR->CONTROLS[1].CnV = 0;

	}
}
