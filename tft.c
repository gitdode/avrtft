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
    displayCmd(0x01);
    displayDes();

    _delay_ms(120);

    // SLPOUT
    displaySel();
    displayCmd(0x11);
    displayDes();
    
    // NORON
    displaySel();
    displayCmd(0x13);
    displayDes();
    
    // COLMOD
    displaySel();
    displayCmd(0x3a);
    displayData(0b00111101);
    displayDes();
    
    // MADCTL
    displaySel();
    displayCmd(0x36);
    displayData(0b01110110);
    displayDes();
    
    // CASET
    uint16_t ys = 0;
    uint16_t ye = 79;
    displaySel();
    displayCmd(0x2a);
    displayData(ys >> 8);
    displayData(ys);
    displayData(ye >> 8);
    displayData(ye);
    displayDes();
    
    // RASET
    uint16_t xs = 0;
    uint16_t xe = 127;
    displaySel();
    displayCmd(0x2b);
    displayData(xs >> 8);
    displayData(xs);
    displayData(xe >> 8);
    displayData(xe);
    displayDes();
    
    // RAMWR
    displaySel();
    displayCmd(0x2c);
    displaySetData();
    for (uint16_t i = 0; i < 42 * 80; i++) {
        transmit(0b11111000);
        transmit(0b00000000);
    }
    for (uint16_t i = 0; i < 43 * 80; i++) {
        transmit(0b00000111);
        transmit(0b11100000);
    }
    for (uint16_t i = 0; i < 43 * 80; i++) {
        transmit(0b00000000);
        transmit(0b00011111);
    }
    displayDes();
    
    // CASET
    ys = 80;
    ye = 159;
    displaySel();
    displayCmd(0x2a);
    displayData(ys >> 8);
    displayData(ys);
    displayData(ye >> 8);
    displayData(ye);
    displayDes();
    
    // RASET
    xs = 0;
    xe = 127;
    displaySel();
    displayCmd(0x2b);
    displayData(xs >> 8);
    displayData(xs);
    displayData(xe >> 8);
    displayData(xe);
    displayDes();
    
    // RAMWR
    displaySel();
    displayCmd(0x2c);
    displaySetData();
    for (uint16_t i = 0; i < 42 * 80; i++) {
        transmit(~0b11111000);
        transmit(~0b00000000);
    }
    for (uint16_t i = 0; i < 43 * 80; i++) {
        transmit(~0b00000111);
        transmit(~0b11100000);
    }
    for (uint16_t i = 0; i < 43 * 80; i++) {
        transmit(~0b00000000);
        transmit(~0b00011111);
    }
    displayDes();
    
    // DISPON
    displaySel();
    displayCmd(0x29);
    displayDes();
    
    // SLPIN
    // displaySel();
    // displayCmd(0x10);
    // displayDes();
    
    printString("done initializing display\r\n");
}

void updateDisplay(void) {
    displaySel();
    
    displayDes();
    
    printString("done updating display\r\n");
}