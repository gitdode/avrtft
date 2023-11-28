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
    
    rgb[0] = grey;
    rgb[0] &= ~0b00001111;
    rgb[0] |= grey4 << 3;
    rgb[0] |= (grey >> 5);

    rgb[1] = (grey << 3);
    rgb[1] &= ~0b01111111;
    rgb[1] |= (grey4 << 6) | (grey4 << 5);
    rgb[1] |= (grey >> 3);
    rgb[1] &= ~0b00000001;
    rgb[1] |= (grey4 << 0);

    rgb[2] = (grey << 4);
    rgb[2] |= (grey >> 1);
    rgb[2] |= (grey0 << 3);

    rgb[3] = (grey << 7);
    rgb[3] |= (grey << 1);
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

void displaySetCmd(void) {
    PORT_DSPI &= ~(1 << PIN_DC);
}

void displaySetData(void) {
    PORT_DSPI |= (1 << PIN_DC);
}

void displayCmd(uint8_t cmd) {
    displaySetCmd();
    transmit(cmd);
}

void displayData(uint8_t data) {
    displaySetData();
    transmit(data);
}

void initDisplay(void) {
    // Hardware reset
    hwReset();

    // TODO necessary?
    _delay_ms(120);

    // Software reset
    displaySel();
    displayCmd(SWRESET);
    displayDes();

    // TODO necessary?
    _delay_ms(120);

    // Sleep out & booster on
    displaySel();
    displayCmd(SLPOUT);
    displayDes();

    // Partial off (Normal)
    displaySel();
    displayCmd(NORON);
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

void fillArea(row_t row, col_t col,
              width_t width, height_t height,
              uint16_t color) {

    // X address start/end
    uint16_t xs = col;
    uint16_t xe = col + width - 1;
    displaySel();
    displayCmd(CASET);
    displayData(xs >> 8);
    displayData(xs);
    displayData(xe >> 8);
    displayData(xe);
    displayDes();

    // Y address start/end
    uint16_t ys = row;
    uint16_t ye = row + height - 1;
    displaySel();
    displayCmd(RASET);
    displayData(ys >> 8);
    displayData(ys);
    displayData(ye >> 8);
    displayData(ye);
    displayDes();

    // Memory write
    displaySel();
    displayCmd(RAMWR);
    displaySetData();

    bytes_t bytes = width * height;
    for (uint16_t i = 0; i < bytes; i++) {
        transmit(color >> 8);
        transmit(color);
    }

    displayDes();    
}

void setArea(row_t row, col_t col, 
             width_t width, height_t height, 
             bool hflip) {
    
    // Memory data access control
    uint8_t madctl = 0b01110110;
    if (hflip) {
        madctl = 0b00110110;
    }
    displaySel();
    displayCmd(MADCTL);
    displayData(madctl);
    displayDes();

    // X address start/end
    uint16_t xs = col;
    uint16_t xe = col + width - 1;
    displaySel();
    displayCmd(CASET);
    displayData(xs >> 8);
    displayData(xs);
    displayData(xe >> 8);
    displayData(xe);
    displayDes();

    // Y address start/end
    uint16_t ys = row;
    uint16_t ye = row + height - 1;
    if (hflip) {
        xs = DISPLAY_HEIGHT - row - height;
        xe = DISPLAY_HEIGHT - row - 1;
    }
    displaySel();
    displayCmd(RASET);
    displayData(ys >> 8);
    displayData(ys);
    displayData(ye >> 8);
    displayData(ye);
    displayDes();
}

void writeData(const __flash uint8_t *bitmap,
               width_t width, height_t height,
               space_t space) {
    // Memory write
    displaySel();
    displayCmd(RAMWR);
    displaySetData();
    
    if (space == SPACE_GREY4) {
        bytes_t bytes = width * height / 2;
        for (uint16_t i = 0; i < bytes; i++) {
            uint8_t rgb[4];
            grey4ToRGB16(bitmap[i], rgb);
            for (uint8_t j = 0; j < 4; j++) {
                transmit(rgb[j]);
            }
        }
    } else {
        // SPACE_RGB16
        bytes_t bytes = width * height * 2;
        for (uint16_t i = 0; i < bytes; i++) {
            transmit(bitmap[i]);
        }        
    }

    displayDes();
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
