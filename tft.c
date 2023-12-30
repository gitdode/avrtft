/* 
 * File:   tft.c
 * Author: torsten.roemer@luniks.net
 *
 * Created on 6. November 2023, 18:45
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <util/delay.h>
#include "tft.h"
#include "pins.h"
#include "usart.h"
#include "spi.h"

#include "bitmaps.h"

/*
 * Converts the given two pixel in 4-Bit greyscale to 16-Bit RGB (5/6/5) color
 * stored in the given array of four bytes.
 * 
 * @param grey two pixel in 4-Bit greyscale
 * @param rgb two pixel in 16-Bit RGB (5/6/5) color
 */
static void grey4ToRGB16(uint8_t grey, uint8_t *rgb) {
    uint8_t grey4 = ((grey >> 4) & 1);
    uint8_t grey0 = ((grey >> 0) & 1);
    
    rgb[0] = (grey & 0xf0);
    rgb[0] |= grey4 << 3;
    rgb[0] |= (grey >> 5);

    rgb[1] = ((grey & 0xf0) << 3);
    rgb[1] |= (grey4 << 6) | (grey4 << 5);
    rgb[1] |= ((grey & 0xf0) >> 3);
    rgb[1] |= (grey4 << 0);

    rgb[2] = (grey << 4);
    rgb[2] |= (grey0 << 3);
    rgb[2] |= ((grey & 0x0f) >> 1);

    rgb[3] = (grey << 7);
    rgb[3] |= ((grey & 0x0f) << 1);
    rgb[3] |= (grey0 << 6) | (grey0 << 5) | (grey0 << 0);    
}

/**
 * Does a hardware reset.
 */
static void hwReset(void) {
    PORT_DISP &= ~(1 << PIN_RST);
    _delay_ms(10);
    PORT_DISP |= (1 << PIN_RST);
}

/**
 * Sets display to send a command.
 */
static void displaySetCmd(void) {
    PORT_DSPI &= ~(1 << PIN_DC);
}

/**
 * Sets display to send data.
 */
static void displaySetData(void) {
    PORT_DSPI |= (1 << PIN_DC);
}

/**
 * Sends the given command to the display.
 * 
 * @param cmd
 */
static void displayCmd(uint8_t cmd) {
    displaySetCmd();
    transmit(cmd);
}

/**
 * Sends the given data to the display.
 * 
 * @param data
 */
static void displayData(uint8_t data) {
    displaySetData();
    transmit(data);
}

/**
 * Sets horizontal and/or vertical flip.
 * 
 * @param hflip
 * @param vflip
 */
static void madctl(bool hflip, bool vflip) {
    // Memory data access control
    uint8_t madctl = 0b11110110;
    madctl &= ~(VFLIP << 7);
    madctl &= ~(HFLIP << 6);
    madctl |= (BGR << 3);

    if (vflip) {
        // Row Address Order (MY)
        madctl ^= (1 << 7);
    }
    if (hflip) {
        // Column Address Order (MX)
        madctl ^= (1 << 6);
    }

    displaySel();
    displayCmd(MADCTL);
    displayData(madctl);
    displayDes();
}

/**
 * Sets the given column start and end address.
 * 
 * @param xs start address
 * @param xe end address
 */
static void caset(uint16_t xs, uint16_t xe) {
    displaySel();
    displayCmd(CASET);
    displayData(xs >> 8);
    displayData(xs);
    displayData(xe >> 8);
    displayData(xe);
    displayDes();
}

/**
 * Sets the given row start and end address.
 * 
 * @param ys start address
 * @param ye end address
 */
static void raset(uint16_t ys, uint16_t ye) {
    displaySel();
    displayCmd(RASET);
    displayData(ys >> 8);
    displayData(ys);
    displayData(ye >> 8);
    displayData(ye);
    displayDes();
}

void initDisplay(void) {
    // Hardware reset
    hwReset();

    // TODO necessary?
    _delay_ms(10);

    // Software reset
    displaySel();
    displayCmd(SWRESET);
    displayDes();

    // TODO necessary?
    _delay_ms(10);

    // Sleep out & booster on
    displaySel();
    displayCmd(SLPOUT);
    displayDes();

    // Partial off (Normal)
    displaySel();
    displayCmd(NORON);
    displayDes();

    // Display Inversion on/off
    displaySel();
    displayCmd(INVOFF + INVERT); // INVOFF + 1 = INVON
    displayDes();

    // Interface pixel format
    displaySel();
    displayCmd(COLMOD);
    displayData(0b00111101);
    displayDes();
    
    // Display on
    displaySel();
    displayCmd(DISPON);
    displayDes();
    
    // Sleep in & booster off
    // displaySel();
    // displayCmd(SLPIN);
    // displayDes();
    
    printString("done initializing display\r\n");
}

void writeStart(void) {
    // Memory write
    displaySel();
    displayCmd(RAMWR);
    displaySetData();
}

void writeByte(uint8_t byte) {
    // Memory write
    transmit(byte);
}

void writeEnd(void) {
    // Memory write
    displayDes();
}

void fillArea(row_t row, col_t col,
              width_t width, height_t height,
              uint16_t color) {

    madctl(false, false);

    // X address start/end
    uint16_t xs = col;
    uint16_t xe = col + width - 1;
    caset(xs, xe);

    // Y address start/end
    uint16_t ys = row;
    uint16_t ye = row + height - 1;
    raset(ys, ye);

    writeStart();

    bytes_t pixels = (bytes_t)width * (bytes_t)height;
    for (bytes_t i = 0; i < pixels; i++) {
        transmit(color >> 8);
        transmit(color);
    }

    writeEnd();
}

void setArea(row_t row, col_t col, 
             width_t width, height_t height, 
             bool hflip, bool vflip) {

    madctl(hflip, vflip);

    // X address start/end
    uint16_t xs = col;
    uint16_t xe = col + width - 1;
    if (vflip) {
        xs = DISPLAY_WIDTH - col - width;
        xe = DISPLAY_WIDTH - col - 1;
    }
    caset(xs, xe);

    // Y address start/end
    uint16_t ys = row;
    uint16_t ye = row + height - 1;
    if (hflip) {
        ys = DISPLAY_HEIGHT - row - height;
        ye = DISPLAY_HEIGHT - row - 1;
    }
    raset(ys, ye);
}

void writeData(const __flash uint8_t *bitmap,
               width_t width, height_t height,
               space_t space) {
    writeStart();
    
    if (space == SPACE_GREY4) {
        bytes_t bytes = (bytes_t)width * (bytes_t)height / 2;
        for (bytes_t i = 0; i < bytes; i++) {
            uint8_t rgb[4];
            grey4ToRGB16(bitmap[i], rgb);
            for (uint8_t j = 0; j < 4; j++) {
                transmit(rgb[j]);
            }
        }
    } else {
        // SPACE_RGB16
        bytes_t bytes = (bytes_t)width * (bytes_t)height * 2;
        for (bytes_t i = 0; i < bytes; i++) {
            transmit(bitmap[i]);
        }        
    }

    writeEnd();
}
