/*receiver code example, prints the received payload to the Serial monitor in HEX format*/
/*static payload length of 1 byte, 1Mbps datarate, -6 dbm rf transmit power, channel 32 of 125 chanels*/
extern "C"{
	#include "nrf24l01.h"
}

void setup()
{
  Serial.begin(115200);
  nrf24_device(RECEIVER, RESET);      //initializing nrf24l01+ as a receiver device with one simple function call
}

void loop()
{
  uint8_t received_payload;
  while(nrf24_receive(&received_payload, 1) == RECEIVE_FIFO_EMPTY)    //poll and receive in one simple function call
    ;
  Serial.println(received_payload, HEX);
}
