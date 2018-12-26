#ifndef ESP8266_H
#define ESP8266_H

#include "LPC407x_8x_177x_8x.h"

#include "Serial.h"

#include <stdio.h>
#include <string.h>

#define ESP8266BufferSize 256

#define ESP8266_UART_BASE    0x4009C000
#define ESP8266_UART    ((UART_TypeDef*) ESP8266_UART_BASE)

#define ESP8266_UART_TX_PIN_ADDRESS    0x4002C000
#define ESP8266_UART_TX_PIN    *((volatile uint32_t*)(ESP8266_UART_TX_PIN_ADDRESS))

#define ESP8266_UART_RX_PIN_ADDRESS    0x4002C004
#define ESP8266_UART_RX_PIN    *((volatile uint32_t*)(ESP8266_UART_RX_PIN_ADDRESS))

extern uint8_t esp8266CurrentBufferIndex;
extern uint8_t esp8266ResponseStartIndex;
extern uint8_t esp8266ResponseCurrentIndex;

extern char esp8266Buffer[ESP8266BufferSize];
extern char esp8266Response[ESP8266BufferSize];

void ESP8266_Init(void);

void ESP8266_sendCommand(char *command);

uint8_t ESP8266_waitResponseEnd(void);

char *ESP8266_readResponse(void);

void ESP8266_clearBuffer(void);

char ESP8266_ReadData(void);

void ESP8266_WriteData(char data);

void ESP8266_Write(char *data);

// CH_PD PIN
#define CH_PD_PORT PORT0
#define CH_PD_MASK ((uint32_t) 1 << 8)

// RST PIN
#define RST_PORT PORT0
#define RST_MASK ((uint32_t) 1 << 7)

#endif
