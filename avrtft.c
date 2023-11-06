/*
 * avrink.c
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation, version 2.
 *
 * Experimental project to drive a TFT display with an ST7735 driver.
 *
 * Created on: 06.11.2023
 *     Author: torsten.roemer@luniks.net
 *
 */

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <util/delay.h>

#include "pins.h"
#include "usart.h"
#include "spi.h"
#include "tft.h"
#include "cmd.h"
#include "bitmaps.h"
#include "display.h"
#include "utils.h"

/* Timer0 interrupts per second */
#define INTS_SEC  F_CPU / (256UL * 255)

static bool once = false;
static volatile uint16_t ints = 0;

ISR(TIMER0_COMPA_vect) {
    ints++;
}

/**
 * Sets up the pins.
 */
static void initPins(void) {
    // set LED pin as output pin
    DDR_LED |= (1 << PIN_LED);

    // set MOSI and SCK as output pin
    DDR_SPI |= (1 << PIN_MOSI);
    DDR_SPI |= (1 << PIN_SCK);
    // drive SS (ensure master) and MISO high
    PORT_SPI |= (1 << PIN_SS);
    PORT_SPI |= (1 << PIN_MISO);

    // set display CS, D/C and RST pin as output pin
    DDR_DSPI |= (1 << PIN_DCS);
    DDR_DSPI |= (1 << PIN_DC);
    DDR_DISP |= (1 << PIN_RST);

    // drive SPI and display output pins high
    PORT_DSPI |= (1 << PIN_DCS);
    PORT_DSPI |= (1 << PIN_DC);
    PORT_DISP |= (1 << PIN_RST);
}

/**
 * Enables SPI master mode.
 */
static void initSPI(void) {
    SPCR |= (1 << SPR0);
    SPCR |= (1 << MSTR);
    SPCR |= (1 << SPE);
}

/**
 * Sets up the timer.
 */
static void initTimer(void) {
    // timer0 clear timer on compare match mode, TOP OCR0A
    TCCR0A |= (1 << WGM01);
    // timer0 clock prescaler/256/255 ~ 123 Hz @ 8 MHz
    TCCR0B |= (1 << CS02);
    OCR0A = 255;

    // enable timer0 compare match A interrupt
    TIMSK0 |= (1 << OCIE0A);
}

/**
 * Turns the LED on.
 */
static void ledOn(void) {
    PORT_LED |= (1 << PIN_LED);
}

/**
 * Turns the LED off.
 */
static void ledOff(void) {
    PORT_LED &= ~(1 << PIN_LED);
}

int main(void) {

    initUSART();
    initPins();
    initSPI();
    initTimer();

    // enable global interrupts
    sei();

    while (true) {
        
        // show a demo once at the start
        if (!once) {
            setFrame(0x00);
            writeBitmap(1, 198, TUX);
            unifontDemo();
            // max resolution image
            // writeBitmap(0, 0, PHOTO);
            display();
            once = true;
        }

        if (ints >= INTS_SEC * 3) {
            ints = 0;
            ledOn();
            // do something and update the display
            _delay_ms(100);
            ledOff();
        }

        if (isUSARTReceived()) {
            char data[USART_LENGTH];
            getUSARTData(data, USART_LENGTH);
            handleCmd(data);
        }
    }

    return 0;
}
