___________________________________________nRF24L01+ C LIBRARY
* version 1.0
* Reza Ebrahimi

This library is written in portable C, and is MCU independant. It consumes a small amount of RAM (under 50 bytes) and program memory (under 2 KB). In order to implement it to your MCU of choice, you need to manipulate functions inside nrf24l01_low_level.c file (SPI, pin configurations) and leave other files as they are. This library is written based on the nRF24L01+ Preliminary Product Specification released by Nordic Semiconductor and is not influenced by other (probably numorous) libraries out there. Any resemblance to pre-existing code is unintentional.

You can use this library in any way, shape or form. I'd be very happy if you mention my name though.

___________________________________________HOW TO USE

As mentioned earlier, first you need to implement low level settings like SPI, delay function and pin configurations inside nrf24l01_low_level.c file (LEVEL 1).

Start by calling nrf24_device(uint8_t device_mode, uint8_t reset_state) function. You can set the device mode to either TRANSMITTER, RECEIVER, POWER_SAVING or TURN_OFF and reset_state to RESET or NO_RESET. if this is the first time nrf24_device is called, nrf24l01+ is reset regardless of reset_state. nrf24_device initializes the low level API like SPI etc, and sets nrf24l01+ with default values and settings. These settings and values can be changed with manipulating macros inside nrf24l01.h, or by calling LEVEL 3 functions. the next steps depend on the chosen device_mode.

For TRANSMITTER:
Use nrf24_transmit(uint8_t *payload, uint8_t payload_width, uint8_t acknowledgement_state) to send an array of 1 byte blocks, with the specified payload_width and acknowledgement_state (could be ACK_MODE or NO_ACK_MODE). If nrf24l01+ is set to static payload width, payload_width is ignored. nrf24_transmit has 2 different outputs: TRANSMIT_BEGIN and TRANSMIT_FAIL (in case of wrong mode of operation or full TX FIFO buffer). Next, you can use nrf24_transmit_status() which has no input, but gives back status: TRANSMIT_IN_PROGRESS if the payload is still not sent or if TX buffer is empty, TRANSMIT_DONE if the payload is sent successfully, TRANSMIT_FAILED if the payload has reached he maximum number of retransmits (only in ACK_MODE).

For RECEIVER:
nrf24_receive(uint8_t *payload, uint8_t payload_width) can be used to both poll the RX buffer, and receive the payload if its already inside the buffer. payload_width is ignored if nrf24l01+ was set to static payload width mode. nrf24_receive outputs the polling results as: OPERATION_ERROR if not in RECEIVER mode, RECEIVE_FIFO_EMPTY in case of empty buffer (payload array is not updated) and OPERATION_DONE if the received dat is saved inside payload array.

For POWER_SAVING or TURN_OFF:
You cannot send or receive any data in these modes of operation, these are used only to reduce power consumption. device_mode can be changed mid code.

General considerations:
the default value for transmit radio power is set to -6 dbm.
the default value for radio channel is set to channel 32.
the default payload width is 1 byte and its static.
the default value for datarate is 1Mbps.

___________________________________________HOW IT WORKS

Functions can be categorized into different levels: from low level APIs up to higher ones.
Lower level APIs are used by higher level APIs. Use LEVEL 4 functions (or sometimes LEVEL 3, 
if you want to change settings) in your firmware.

LEVEL 1:
 *  void delay_function(uint32_t duration_ms)
 *  void SPI_Initializer()
 *  void pinout_Initializer()
 *  void nrf24_SPI(uint8_t input)
 *  uint8_t SPI_send_command(uint8_t command)
 *  void nrf24_CE(uint8_t input)
 
LEVEL 2:
 *  void nrf24_write(uint8_t address, uint8_t *value, uint8_t data_length, uint8_t spi_state)
 *  void nrf24_read(uint8_t address, uint8_t *value, uint8_t data_length, uint8_t spi_state)
 *  void nrf24_send_payload(uint8_t *payload, uint8_t payload_width)
 
LEVEL 3:
 *  void nrf24_mode(uint8_t mode)
 *  void nrf24_crc_configuration(uint8_t crc_enable, uint8_t crc_encoding_scheme)
 *  void nrf24_interrupt_mask(uint8_t rx_mask, uint8_t tx_mask, uint8_t max_rt_mask)
 *  void nrf24_rf_channel(uint8_t rf_channel)
 *  void nrf24_rf_power(uint8_t rf_power)
 *  void nrf24_rf_datarate(uint8_t rf_datarate)
 *  void nrf24_address_width(uint8_t address_width)
 *  void nrf24_datapipe_enable(uint8_t number_of_datapipes)
 *  void nrf24_prx_static_payload_width(uint8_t static_payload_width, uint8_t number_of_datapipes)
 *  void nrf24_datapipe_address_configuration()
 *  void nrf24_datapipe_ptx(uint8_t datapipe_number)
 *  void nrf24_dynamic_payload(uint8_t state, uint8_t datapipe)
 *  void nrf24_auto_acknowledgment_setup(uint8_t datapipe)
 *  void nrf24_automatic_retransmit_setup(uint16_t delay_time, uint8_t retransmit_count)
 *  void nrf24_dynamic_ack(uint8_t state)
  
LEVEL 4:
 *  void nrf24_device(uint8_t device_mode, uint8_t reset_state)
 *  void nrf24_reset()
 *  uint8_t nrf24_flush(uint8_t fifo_select)
 *  uint8_t nrf24_receive(uint8_t *payload, uint8_t payload_width)
 *  uint8_t nrf24_transmit_status()
 *  uint8_t nrf24_transmit(uint8_t *payload, uint8_t payload_width, uint8_t acknowledgement_state)

