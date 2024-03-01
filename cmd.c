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
 * Writes one line of text to the given row and column.
 * @param data
 */
static void text(char *data) {
    strtok(data, " ");
    char *end;
    row_t row = strtol(strtok(NULL, " "), &end, 10);
    col_t col = strtol(strtok(NULL, " "), &end, 10);
    char *text = strtok(NULL, "\0");
    
    const __flash Font *hack = &hackFont;
    writeString(row, col, hack, text);
}

/**
 * Writes the bitmap with the given index to the given row and column.
 * @param data
 */
static void bitmap(char *data) {
    strtok(data, " ");
    char *end;
    row_t row = strtol(strtok(NULL, " "), &end, 10);
    col_t col = strtol(strtok(NULL, " "), &end, 10);
    uint8_t index = strtol(strtok(NULL, " "), &end, 10);
    
    writeBitmap(row, col, index);
}

static void bmp(char *data) {
    strtok(data, " ");
    char *end;
    row_t row = strtol(strtok(NULL, " "), &end, 10);
    col_t col = strtol(strtok(NULL, " "), &end, 10);
    
    prepare(row, col);
}

static void bmpSD(char *data) {
    strtok(data, " ");
    char *end;
    uint32_t address = strtol(strtok(NULL, " "), &end, 10);
    
    if (sdcard) {
        readSD(address);
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
