#include "MKL25Z4.h"
#include "nrf.h"
#include "spi0.h"
#include "led.h"
#include "uart.h"
void nrf_config_write() //write to the config register
{
	TEST_LOW; //toggle CS
	nrf_write_register(NORDIC_CONFIG_REG);
	spi_send_byte(0x03);
	TEST_HIGH;  //toggle CS
}

void nrf_config_read() //read from the config register
{
	char c;
	TEST_LOW;
	nrf_read_register(NORDIC_CONFIG_REG);
    c =spi_send_byte(0XFF);
	//c=spi_receive_byte();
	TEST_HIGH;
	if (c==0x03)
	{
		Initialize_LED();
	      Intensty_Modify(CYAN, 900);
	}
}

void nrf_write_register(unsigned char address) //write command
{
	spi_send_byte(0x20|address);
}

void nrf_read_register(unsigned char address) //read command
{
	spi_send_byte(0x00|address);
}

void nrf_flush_tx_fifo() //empty the nrf tx buffer
{
	TEST_LOW;
	spi_send_byte(0xE1);
	TEST_HIGH;
}

void nrf_flush_rx_fifo() //empty the nrf rx buffer
{
	TEST_LOW;
	spi_send_byte(0xE2);
	TEST_HIGH;
}

void nrf_transmit_data() //send data to nrf buffer
{
	TEST_LOW;
	spi_send_byte(W_TXPAYLOAD);
	spi_send_byte(0x10);
	TEST_HIGH;
}

void nrf_read_data() //receive data from nrf buffer
{
	char c;
	TEST_LOW;
	spi_send_byte(R_RXPAYLOAD);
	spi_send_byte(0xff);
	c=spi_receive_byte();
	TEST_HIGH;

	nrf_fifostatus_read();

	if (c==0x07) //poll for data 07 from the tx
	{
		PTB_BASE_PTR->PDDR |= 1<<18;

	}
}

void nrf_status_read() //read the status register
{
	char c;
	TEST_LOW;
	nrf_read_register(NORDIC_STATUS_REG);
	spi_send_byte(0xFF);
	c=spi_receive_byte();
	TEST_HIGH;
}

void nrf_rfsetup_transmit() //setup the rf register
{
	TEST_LOW;
	nrf_write_register(NORDIC_RF_SETUP_REG);
	spi_send_byte(0x84);
	TEST_HIGH;
}

void nrf_rfsetup_receive() //read the rf register
{
	char c;
	TEST_LOW;
	nrf_write_register(NORDIC_RF_SETUP_REG);
	spi_send_byte(0xff);
	 c=spi_receive_byte();
	TEST_HIGH;

}

void nrf_fifostatus_read() //read the fifo register
{
	char c;
	TEST_LOW;
	nrf_read_register(FIFO_STATUS_REG );
	spi_send_byte(0xff);
	 c=spi_receive_byte();
	 TEST_HIGH;
}

void nrf_tx_addr_read() //read the tx address register
{
	int i;
	char c;
	TEST_LOW;
	nrf_read_register(TX_ADDR);
	 for(i=0;i<5;i++)
	 {
		 spi_send_byte(0xff);
		 c=spi_receive_byte();
	 }
	TEST_HIGH;
}

void nrf_tx_addr_write() //write the tx address register
{
	int i;
	TEST_LOW;
	nrf_write_register(TX_ADDR);
	 for(i=0;i<5;i++)
	 {
		 spi_send_byte(0xBB);
	 }
	 TEST_HIGH;
}

void nrf_rx_addr_read() //read the rx address register
{
	int i;
	char c;
	TEST_LOW;
	nrf_read_register(RX_ADDR_P0_REG);
	 for(i=0;i<5;i++)
	 {
		 spi_send_byte(0xff);
		 c=spi_receive_byte();
	 }
	TEST_HIGH;
}

void nrf_rx_addr_write() //write the rx address register
{
	int i;
	TEST_LOW;
	nrf_write_register(RX_ADDR_P0_REG);
	 for(i=0;i<5;i++)
	 {
		 spi_send_byte(0xE7);
	 }
	 TEST_HIGH;
}

void nrf_en_rxaddr_write() //write to the datapipe register
{
	int i;
	TEST_LOW;
	nrf_write_register(NRF_ENRXADDR);

	spi_send_byte(0x01);

	 TEST_HIGH;
}

void nrf_en_rxaddr_read() //read from the datapipe register
{
	int i;
	char c;
	TEST_LOW;
	nrf_read_register(NRF_ENRXADDR);

	 spi_send_byte(0xff);
	 c=spi_receive_byte();

	 TEST_HIGH;
}


void nrf_rx_pipesize_write() //set the data pipe size
{
	int i;
	TEST_LOW;
	nrf_write_register(NRF_PIPESIZE);

	spi_send_byte(0x01);

	TEST_HIGH;
}

void nrf_rx_pipesize_read()  //read the data pipe size
{
	int i;
	char c;
	TEST_LOW;
	nrf_read_register(NRF_PIPESIZE);

	 spi_send_byte(0xff);
	 c=spi_receive_byte();

	 TEST_HIGH;
}
