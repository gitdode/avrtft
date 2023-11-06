/* 
 * File:   tft.c
 * Author: torsten.roemer@luniks.net
 * Thanks to https://github.com/adafruit/Adafruit-ST7735-Library for helping me out!
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
    displaySel();
 
    printString("done initializing display\r\n");
    
    displayDes();
}

void updateDisplay(void) {
    displaySel();
    
    printString("done updating display\r\n");
    
    displayDes();
}