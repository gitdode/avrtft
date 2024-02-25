/*
 * avrink.c
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation, version 2.
 *
 * Experimental project to drive a TFT display with an ST7735R driver.
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
#include "bmp.h"
#include "touch.h"
#include "paint.h"
#include "sdcard.h"

static volatile bool touch = false;

ISR(INT0_vect) {
    touch = true;
}

/**
 * Sets up the pins.
 */
static void initPins(void) {
    // set MOSI and SCK as output pin
    DDR_SPI |= (1 << PIN_MOSI);
    DDR_SPI |= (1 << PIN_SCK);
    // drive SS (ensure master) and MISO high
    PORT_SPI |= (1 << PIN_SS);
    PORT_SPI |= (1 << PIN_MISO);

    // set SDA and SCL as output pin
    // DDR_I2C |= (1 << PIN_SCL);
    // DDR_I2C |= (1 << PIN_SDA);

    // set SD card reader CS as output pin
    DDR_SDC |= (1 << PIN_SDCS);

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
    // min speed for a cool visual effect :-)
    // SPCR |= (1 << SPR1) | (1 << SPR0);
    SPCR |= (1 << MSTR);
    SPCR |= (1 << SPE);
}

/**
 * Enables I2C.
 */
static void initI2C(void) {
    // 100 kHz @ 16 Mhz
    TWBR = 72;
    TWCR |= (1 << TWEN);
}

/**
 * Enables touch interrupt.
 */
static void initTouchInt(void) {
    EIMSK |= (1 << INT0);
    // EICRA |= (1 << ISC00); // interrupt on any logical change
    EICRA |= (1 << ISC01); // interrupt on falling edge
    // EICRA |= (1 << ISC01) | (1 << ISC00); // interrupt on rising edge
}

int main(void) {

    initUSART();
    initPins();
    initSPI();
    initSDCard();
    initI2C();

    // enable global interrupts
    sei();

    _delay_ms(1000);

    initDisplay();
    initTouchInt();

    // ignore initial touch interrupt
    _delay_ms(1);
    touch = false;

    // do something at the start
    initPaint();
    // hackDemo();

    while (true) {
        if (touch) {
            touch = false;
            Point point = {0};
            // memset(&point, 0, sizeof (Point));
            uint8_t event = readTouch(&point);
            paintEvent(event, &point);
        }

        if (isStreamingData()) {
            char data = UDR0;
            stream(data);
        }

        // TODO block while busy?
        if (isUSARTReceived()) {
            char data[USART_LENGTH];
            getUSARTData(data, USART_LENGTH);
            handleCmd(data);
        }
    }

    return 0;
}
