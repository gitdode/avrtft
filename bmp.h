/* 
 * File:   bmp.h
 * Author: torsten.roemer@luniks.net
 *
 * Created on 22. November 2023, 23:10
 */

#ifndef BMP_H
#define BMP_H

#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "types.h"
#include "sdcard.h"
#include "display.h"
#include "tft.h"
#include "usart.h"
#include "hack.h"
#include "touch.h"

#define BMP_READY   0
#define BMP_BUSY    1
#define BMP_ERROR   2

/**
 * Handles the given touch event and point.
 * 
 * @param event
 * @param point
 */
void bmpEvent(uint8_t event, Point *point);

/**
 * Prepares to "stream" a BMP image via USART to the display,
 * with its upper left corner at the given coordinates.
 * 
 * @param row
 * @param col
 */
void prepareBMP(row_t row, col_t col);

/**
 * Does basic parsing of the BMP image (16-Bit 5/6/5 RGB) sent via USART and 
 * sends the image pixels to the display.
 * Image dimensions have to be '(w * h * 2) % 4 = 0' because padded rows 
 * are currently not supported.
 * 
 * @param byte raw BMP byte recieved via USART
 * @return status current status parsing BMP
 */
uint8_t streamBMP(uint8_t byte);

/**
 * Reads a BMP image raw from the SD card starting at the given address.
 * 
 * @param address start address
 */
void readBMPFromSD(uint32_t address);

#endif /* BMP_H */

