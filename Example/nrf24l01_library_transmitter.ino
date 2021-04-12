/*transmitter code*/
#include "nrf24l01.h"

uint8_t temp = 0X00;

void setup()
{
  Serial.begin(115200);
  nrf24_device(TRANSMITTER, RESET);
}

void loop()
{
  delay(500);
  
  nrf24_transmit(&temp, 1, NO_ACK_MODE);
  temp++;
  delay(10);
  
  while(nrf24_transmit_status() == TRANSMIT_IN_PROGRESS)
  ;
  Serial.println("Sent!");
}
