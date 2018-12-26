#include "Serial.h"
#include "Car.h"

char    *serialTransmitData     = 0;
uint8_t serialTransmitCompleted = 0;
char    serialReceivedCharacter = 0;
char    serialLastCharacter = 0;

void Serial_Init() {
	//Change the function of TX and RX pins for UART.
	uint32_t value1  = Serial_UART_TX_PIN;
	value1 |= 1 << 0;
	value1 &= ~((1 << 1) | (1 << 2));
	Serial_UART_TX_PIN = value1;
	uint32_t value2 = Serial_UART_RX_PIN;
	value2 |= 1 << 0;
	value2 &= ~((1 << 1) | (1 << 2));
	Serial_UART_RX_PIN = value2;

	//Turn on UART0.
	PCONP |= (1 << 3);

	//Enable FIFO for UART0.
	Serial_UART->FCR |= (1 << 0);

	//In order to change the DLM, DLL and FDR values, Write correct code for enabling the access to Divisor Latches.
	Serial_UART->LCR |= (1 << 7);

	//Write correct DLM, DLL and FDR values for 9600 baudrate
	Serial_UART->DLM = (0x01 << 0);
	Serial_UART->DLL = (0x25 << 0);
	Serial_UART->FDR = ((0x01 << 0) | (0x03 << 4));

	//Write correct code for disabling the access to Divisor Latches.
	Serial_UART->LCR &= ~(1 << 7);

	//Change LCR register value for 8-bit character transfer, 1 stop bits and Even Parity.
	Serial_UART->LCR = (3 << 0) | (0 << 2) | (1 << 3) | (1 << 4);

	//Enable the Receive Data Available and THRE Interrupt.
	Serial_UART->IER |= (1 << 0); // RBR Interrupt Enable.
	Serial_UART->IER |= (1 << 1); // THRE Interrupt Enable..

	//Enable UART0_IRQn Interrupt.
	NVIC_EnableIRQ(UART0_IRQn);

	//Set UART0_IRQn Priority to 5.
	NVIC_SetPriority(UART0_IRQn, 5);
//	NVIC_ClearPendingIRQ(TIMER2_IRQn);

}

void UART0_IRQHandler() {
	uint32_t currentInterrupt = ((Serial_UART->IIR & (0x7 << 1)) >> 1);

	//First if statement is for Receive Data Available interrupt.
	if (currentInterrupt == 0x02) {
		serialReceivedCharacter = Serial_ReadData();
		if(serialReceivedCharacter == AUTO){
			Serial_Write("AUTO\r\n");
			setMode(AUTO);
		} else if(serialReceivedCharacter == MANUEL){
			Serial_Write("MANUEL\r\n");
			setMode(MANUEL);
		} else if (serialReceivedCharacter == '6') {
			if(serialLastCharacter == '6') {
				serialLastCharacter = 0;
				if(mode == AUTO) {
					Serial_Write("STARTED\r\n");
					active = 1;
				} else {
					Serial_Write("NOT STARTED\r\n");
				}
			} else {
				serialLastCharacter = '6';
			}
			
		}
	} else if (currentInterrupt == 0x1) {
		//Second if statement is for THRE interrupt
		if (*serialTransmitData > 0) {
			Serial_WriteData(*serialTransmitData++);
		} else {
			serialTransmitCompleted = 1;
		}
	}
}

char Serial_ReadData() {
	return Serial_UART->RBR;
}

void Serial_WriteData(char data) {
	serialTransmitCompleted = 0;
	Serial_UART->THR = data;
}

void Serial_Write(char* data) {
	while(*data > 0) {
		Serial_WriteData(*data++);
	}
}


