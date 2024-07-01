/* 
 * File:   spi.c
 * Author: torsten.roemer@luniks.net
 *
 * Created on 1. April 2023, 18:59
 */

#include <stdio.h>
#include <avr/io.h>
#include "pins.h"
#include "spi.h"

void spiSlow(void) {
    SPCR &= ~(1 << SPR0);
    SPCR |= (1 << SPR1);
    SPSR &= ~(1 << SPI2X);
}

void spiFast(void) {
    SPCR &= ~(1 << SPR1) & ~(1 << SPR0);
    SPSR &= ~(1 << SPI2X);
}

void sdCardSel(void) {
    PORT_SDC &= ~(1 << PIN_SDCS);
}

void sdCardDes(void) {
    PORT_SDC |= (1 << PIN_SDCS);
}

void displaySel(void) {
    PORT_DSPI &= ~(1 << PIN_DCS);
}

void displayDes(void) {
    PORT_DSPI |= (1 << PIN_DCS);
}

uint8_t transmit(uint8_t data) {
    SPDR = data;
    loop_until_bit_is_set(SPSR, SPIF);

    return SPDR;
}