#include "nrf24l01.h"

/*start of low level functions, specific to the mcu and compiler*/

/*delay in miliseconds*/
void delay_function(uint32_t duration_ms)
{
}

/*contains all SPI configuations, such as pins and control registers*/
/*SPI control: master, interrupts disabled, clock polarity low when idle, clock phase falling edge, clock up tp 1 MHz*/
void SPI_Initializer()
{
}

/*contains all CSN and CE pins gpio configurations, including setting them as gpio outputs and turning SPI off and CE '1'*/
void pinout_Initializer()
{
}

/*CSN pin manipulation to high or low (SPI on or off)*/
void nrf24_SPI(uint8_t input)
{
}

/*1 byte SPI shift register send and receive routine*/
uint8_t SPI_send_command(uint8_t command)
{
}

/*CE pin maniplation to high or low*/
void nrf24_CE(uint8_t input)
{
}
