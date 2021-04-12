/*transmitter code example, transmits an ascending number every TIME_GAP milliseconds in NO_ACK mode*/
/*static payload length of 1 byte, 1Mbps datarate, -6 dbm rf transmit power, channel 32 of 125 chanels*/
#include "nrf24l01.h"

#define TIME_GAP    500

uint8_t ascending_number = 0X00;                        

void setup()
{
  Serial.begin(115200);                          
  nrf24_device(TRANSMITTER, RESET);     //initializing nrf24l01+ as a transmitter using one simple function
}

void loop()
{
  delay(TIME_GAP);
  while(nrf24_transmit(&ascending_number, 1, NO_ACK_MODE) == TRANSMIT_FAIL)      //wait until payload is loaded into TX buffer
  {
    Serial.println("Transmit fail!");
  }
  while(nrf24_transmit_status() == TRANSMIT_IN_PROGRESS)      //poll the transmit status, make sure the payload is sent
    ;
  Serial.println("Sent!");      //payload is sent without acknowledge successfully
  ascending_number++;
}
