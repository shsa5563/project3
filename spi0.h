/*
 * spi0.h
 *
 *  Created on: 04-Nov-2016
 *      Author: Satyanarayana
 */

#ifndef SOURCES_SPI0_H_
#define SOURCES_SPI0_H_

#define TEST_LOW GPIOC_PCOR |= GPIO_PCOR_PTCO(0x10)  //debug pin
#define TEST_HIGH GPIOC_PSOR |= GPIO_PSOR_PTSO(0x10) //debug pin
#define SPI_WAIT_RX_DATA while (!(SPI0_S & SPI_S_SPRF_MASK))  //waits for the rx data ready ready
#define SPI_WAIT_TX_DATA while (!(SPI0_S & SPI_S_SPTEF_MASK)) //waits for the txef data ready ready
#define SPI_RD_WR_REG SPI0_D  //kinetis read write register
void spi_init();
unsigned char  spi_send_byte(char spiMsg);
unsigned char spi_receive_byte();
void spi_flush();
void spi0_init( void);
void spi_test_io( void);

#endif /* SOURCES_SPI0_H_ */
