/* 
 * File:   cmd.c
 * Author: torsten.roemer@luniks.net
 *
 * Created on 18. April 2023, 21:18
 */

#include <string.h>
#include <stdlib.h>
#include "cmd.h"

extern bool sdcard;

/**
 * Sets the frame buffer to the given 16-Bit (5/6/5) RGB color.
 * @param data
 */
static void clear(char *data) {
    strtok(data, " ");
    char *end;
    uint16_t color = strtol(strtok(NULL, " "), &end, 16);
    
    setFrame(color);
}

/**
 * Writes one line of text to the given x and y coordinates.
 * @param data
 */
static void text(char *data) {
    strtok(data, " ");
    char *end;
    x_t x = strtol(strtok(NULL, " "), &end, 10);
    y_t y = strtol(strtok(NULL, " "), &end, 10);
    char *text = strtok(NULL, "\0");
    
    const __flash Font *hack = &hackFont;
    writeString(x, y, hack, text);
}

/**
 * Writes the bitmap with the given index to the given x and y coordinates.
 * @param data
 */
static void bitmap(char *data) {
    strtok(data, " ");
    char *end;
    x_t x = strtol(strtok(NULL, " "), &end, 10);
    y_t y = strtol(strtok(NULL, " "), &end, 10);
    uint8_t index = strtol(strtok(NULL, " "), &end, 10);
    
    writeBitmap(x, y, index);
}

/**
 * Prepares for writing a BMP image to the given x and y coordinates.
 * @param data
 */
static void bmp(char *data) {
    strtok(data, " ");
    char *end;
    x_t x = strtol(strtok(NULL, " "), &end, 10);
    y_t y = strtol(strtok(NULL, " "), &end, 10);
    
    prepareBMP(x, y);
}

/**
 * Reads a BMP image from SD Card starting at the given address.
 * @param data
 */
static void bmpSD(char *data) {
    strtok(data, " ");
    char *end;
    uint32_t address = strtol(strtok(NULL, " "), &end, 10);
    
    if (sdcard) {
        readBMPFromSD(address);
    } else {
        printString("SD card not inserted?\r\n");
    }
}

/**
 * Writes the Hack demo.
 */
static void demo(void) {
    hackDemo();
}

void handleCmd(char *data) {
    printString("\r\n");
    
    switch(*data) {
        case CMD_CLEAR:  clear(data); break;
        case CMD_TEXT:   text(data); break;
        case CMD_BITMAP: bitmap(data); break;
        case CMD_BMP:    bmp(data); break;
        case CMD_BMP_SD: bmpSD(data); break;
        case CMD_DEMO:   demo(); break;
        case CMD_PAINT:  initPaint(); break;
        default: break;
    }
}
