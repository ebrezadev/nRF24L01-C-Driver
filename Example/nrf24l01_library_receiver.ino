/*receiver code*/
#include "nrf24l01.h"

void setup()
{
  Serial.begin(115200);
  nrf24_device(RECEIVER, RESET);
}

void loop()
{
  uint8_t temp = 0;

  do
  {
    ;
  } while(nrf24_receive(&temp, 1) == RECEIVE_FIFO_EMPTY);

  Serial.print(temp, HEX);
  Serial.println(" message");
}
