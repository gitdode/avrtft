/* 
 * File:   spi.h
 * Author: torsten.roemer@luniks.net
 *
 * Created on 1. April 2023, 19:12
 */

#ifndef SPI_H
#define SPI_H

/**
 * Selects the SD card to talk to via SPI.
 */
void sdCardSel(void);

/**
 * Delects the SD card to talk to via SPI.
 */
void sdCardDes(void);

/**
 * Selects the display to talk to via SPI.
 */
void displaySel(void);

/**
 * Deselects the display to talk to via SPI.
 */
void displayDes(void);

/**
 * Transmits the given byte and returns the byte reveived at the same time.
 * @param data byte to be written
 * @return byte read while writing
 */
uint8_t transmit(uint8_t data);

#endif /* SPI_H */

