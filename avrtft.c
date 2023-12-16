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
#include <util/twi.h>

#include "pins.h"
#include "usart.h"
#include "spi.h"
#include "tft.h"
#include "cmd.h"
#include "bitmaps.h"
#include "display.h"
#include "utils.h"
#include "bmp.h"

#include "i2c.h"
#include "touch.h"

/* Timer0 interrupts per second */
#define INTS_SEC  F_CPU / (256UL * 255)

static bool once = false;
static volatile uint16_t ints = 0;

ISR(TIMER0_COMPA_vect) {
    ints++;
}

static volatile bool touch = false;
static bool busy = false;

ISR(INT0_vect) {
    touch = true;
}

static void readTouch(void) {
    printString("touch!\r\n");
//    i2cStart();
//    i2cSend(FT62XX_ADDRESS);
//    i2cSend(0x03);
//    // i2cStop();
//    
//    i2cStart();
//    i2cSend(FT62XX_ADDRESS + 1);
//    uint8_t xh = i2cReadAck();
//    i2cStop();
    
//    i2cStart();
//    // printUint(0);
//    i2cSend(0x38);
//    // printUint(1);
//    i2cSend(0x00);
//    // i2cStop();
//    // printUint(2);
//    
//    i2cStart();
//    // printUint(3);
//    i2cSend(0x38 + 1);
//    printUint(4);
//    uint8_t xl = i2cReadAck();
//    // printUint(5);
//    i2cStop();
//    printUint(6);
    
    // start
    TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWSTA);
    loop_until_bit_is_set(TWCR, TWINT);
    if ((TWSR & 0xF8) != TW_START) {
        printString("error start\r\n");
        // return;
    }
    // printUint(0);
    
    // send slave address + write
    TWDR = 0x38;
    TWCR = (1 << TWINT) | (1 << TWEN);
    loop_until_bit_is_set(TWCR, TWINT);
    if ((TWSR & 0xF8) != TW_MT_SLA_ACK) {
        printString("error write\r\n");
        // printUint((TWSR & 0xF8));
        // return;
    }
    // printUint(1);
    
    // send data address (DEV_MODE)
    TWDR = 0x00;
    TWCR = (1 << TWINT) | (1 << TWEN);
    loop_until_bit_is_set(TWCR, TWINT);
    if ((TWSR & 0xF8) != TW_MT_DATA_ACK) {
        printString("error data\r\n");
        // return;
    }
    // printUint(2);
    
    // restart
    TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWSTA);
    loop_until_bit_is_set(TWCR, TWINT);
    if ((TWSR & 0xF8) != TW_REP_START) {
        printString("error rep start\r\n");
        // return;
    }
    // printUint(3);
    
    // send slave address + read
    TWDR = 0x38 + 1;
    TWCR = (1 << TWINT) | (1 << TWEN);
    loop_until_bit_is_set(TWCR, TWINT);
    if ((TWSR & 0xF8) != TW_MR_SLA_ACK) {
        printString("error read\r\n");
        // return;
    }
    // printUint(4);
    
    // read with ack
    TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA);
    loop_until_bit_is_set(TWCR, TWINT); // never returns, same w/o ack
    uint8_t response = TWDR;
    // printUint(5);
    
    // stop
    TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWSTO);
    
    printUint(response);
    
//    uint16_t x = 0;
//    // x |= (xh & 0x0f) << 8;
//    x |= xl;
//    
//    char buf[16];
//    snprintf(buf, sizeof (buf), "%u\r\n", x);
//    printString(buf);
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
 * Sets up the timer.
 */
static void initTimer(void) {
    // timer0 clear timer on compare match mode, TOP OCR0A
    TCCR0A |= (1 << WGM01);
    // timer0 clock prescaler/256/255 ~ 123 Hz @ 8 MHz
    TCCR0B |= (1 << CS02);
    OCR0A = 255;

    // enable timer0 compare match A interrupt
    // TIMSK0 |= (1 << OCIE0A);
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
    // set SDA and SCL as output pin
    // DDRC |= (1 << PC5);
    // DDRC |= (1 << PC4);
    
    // 100 kHz @ 16 Mhz
    TWBR = 72;
    TWCR |= (1 << TWEN);
}

/**
 * Enables touch interrupt.
 */
static void initTouchInt(void) {
    EIMSK |= (1 << INT0);
    // EICRA |= (1 << ISC01); // interrupt on falling edge
}

int main(void) {

    initUSART();
    initPins();
    // initTimer();
    initSPI();
    initI2C();

    // enable global interrupts
    sei();

    _delay_ms(1000);
    
    initDisplay();
    initTouchInt();
    
    while (true) {
        
        // show a demo once at the start
//        if (!once) {
//            // setFrame(0x0);
//            hackDemo();
//            once = true;
//        }
        
        if (touch && !busy) {
            busy = true;
            readTouch();
            busy = false;
            touch = false;
        }

//        if (isStreamingData()) {
//            char data = UDR0;
//            stream(data);
//        }

        // TODO block while busy?
//        if (isUSARTReceived()) {
//            char data[USART_LENGTH];
//            getUSARTData(data, USART_LENGTH);
//            handleCmd(data);
//        }
    }

    return 0;
}
