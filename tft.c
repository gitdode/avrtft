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

static void fourBitGreyTo16BitRGB(uint8_t grey, uint8_t *rgb) {
    uint8_t grey4 = ((grey >> 4) & 1);
    uint8_t grey0 = ((grey >> 0) & 1);
    
    uint8_t rgb1m = grey;
    rgb1m &= ~0b00001111;
    rgb1m |= grey4 << 3;
    rgb1m |= (grey >> 5);

    uint8_t rgb1l = (grey << 3);
    rgb1l &= ~0b01111111;
    rgb1l |= (grey4 << 6) | (grey4 << 5);
    rgb1l |= (grey >> 3);
    rgb1l &= ~0b00000001;
    rgb1l |= (grey4 << 0);

    uint8_t rgb2m = (grey << 4);
    rgb2m |= (grey >> 1);
    rgb2m |= (grey0 << 3);

    uint8_t rgb2l = (grey << 7);
    rgb2l |= (grey << 1);
    rgb2l |= (grey0 << 6) | (grey0 << 5) | (grey0 << 0);
    
    rgb[0] = rgb1m;
    rgb[1] = rgb1l;
    rgb[2] = rgb2m;
    rgb[3] = rgb2l;
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
    hwReset();

    _delay_ms(120);

    // SWRESET
    displaySel();
    displayCmd(SWRESET);
    displayDes();

    _delay_ms(120);

    // SLPOUT
    displaySel();
    displayCmd(SLPOUT);
    displayDes();

    // NORON
    displaySel();
    displayCmd(NORON);
    displayDes();

    // COLMOD
    displaySel();
    displayCmd(COLMOD);
    displayData(0b00111101);
    displayDes();

    // MADCTL
    displaySel();
    displayCmd(MADCTL);
    displayData(0b01110110);
    displayDes();
    
    printString("done initializing display\r\n");
}

void writeDisplay(uint16_t row, uint16_t col,
                  const __flash uint8_t *bitmap,
                  width_t width, height_t height,
                  uint8_t color) {
    
    uint16_t bytes = width * height * 2;

    // CASET
    uint16_t ys = col;
    uint16_t ye = col + width - 1;
    displaySel();
    displayCmd(CASET);
    displayData(ys >> 8);
    displayData(ys);
    displayData(ye >> 8);
    displayData(ye);
    displayDes();

    // RASET
    uint16_t xs = row;
    uint16_t xe = row + height - 1;
    displaySel();
    displayCmd(RASET);
    displayData(xs >> 8);
    displayData(xs);
    displayData(xe >> 8);
    displayData(xe);
    displayDes();

    // RAMWR
    displaySel();
    displayCmd(RAMWR);
    displaySetData();

    if (color == COLOR_RGB16) {
        for (uint16_t i = 0; i < bytes; i++) {
            transmit(bitmap[i]);
        }
    }

    if (color == COLOR_GREY4) {
        for (uint16_t i = 0; i < bytes; i++) {
            uint8_t rgb[4];
            fourBitGreyTo16BitRGB(bitmap[i], rgb);
            for (uint8_t j = 0; j < 4; j++) {
                transmit(rgb[j]);
            }                
        }        
    }

    displayDes();    
}

void updateDisplay(void) {

    // DISPON
    displaySel();
    displayCmd(DISPON);
    displayDes();
    
    // SLPIN
    // displaySel();
    // displayCmd(SLPIN);
    // displayDes();
    
    printString("done updating display\r\n");
}