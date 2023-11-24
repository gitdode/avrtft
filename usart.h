/*
 * usart.h
 *
 *  Created on: 19.05.2015
 *      Author: dode@luniks.net
 */

#ifndef USART_H_
#define USART_H_

#include <stdbool.h>
#include <stdio.h>

#define USART_LENGTH 128

#ifndef BAUD
#define BAUD 9600
#endif

extern char usartData[USART_LENGTH];

void pollUSART(void);

/**
 * Sets the baudrate and enables the transmitter and receiver.
 */
void initUSART(void);

/**
 * Returns true if a CR or LF terminated line of data was received via USART.
 */
bool isUSARTReceived(void);

bool isStreaming(void);

void setUSARTReceived(void);

/**
 * Appends the data received via USART to the given string with the given
 * length.
 */
void getUSARTData(char *data, size_t length);

void setStreaming(bool enabled);

/**
 * Prints the given string via USART.
 */
void printString(const char *data);

/**
 * Prints the given unsigned integer including CR + LF via USART.
 */
void printUint(uint8_t data);

/**
 * Prints the given unsigned integer in binary notation including CR + LF
 * via USART.
 */
void printByte(uint8_t data);

#endif /* USART_H_ */
