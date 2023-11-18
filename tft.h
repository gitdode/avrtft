/* 
 * File:   tft.h
 * Author: torsten.roemer@luniks.net
 *
 * Created on 6. November 2023, 18:45
 */

#ifndef TFT_H
#define TFT_H

#include <stdbool.h>
#include "types.h"

#define SWRESET 0x01
#define SLPIN   0x10
#define SLPOUT  0x11
#define NORON   0x13
#define DISPON  0x29
#define CASET   0x2a
#define RASET   0x2b
#define RAMWR   0x2c
#define MADCTL  0x36
#define COLMOD  0x3a

#define DISPLAY_WIDTH   160
#define DISPLAY_HEIGHT  128

#define COLOR_GREY4  0
#define COLOR_RGB16  1

/**
 * Sets display to send a command.
 */
void displaySetCmd(void);

/**
 * Sets display to send data.
 */
void displaySetData(void);

/**
 * Sends the given command to the display.
 */
void displayCmd(uint8_t cmd);

/**
 * Sends the given data to the display.
 */
void displayData(uint8_t data);

/**
 * Initializes the display.
 */
void initDisplay(void);

/**
 * Writes image data to the display.
 */
void writeDisplay(uint16_t row, uint16_t col,
                  const __flash uint8_t *bitmap,
                  width_t width, height_t height,
                  uint8_t color);

#endif /* TFT_H */
