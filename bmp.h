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

/**
 * Prepares to "stream" a BMP image via USART to the display,
 * with its upper left corner at the given coordinates.
 * 
 * @param row
 * @param col
 */
void prepare(row_t row, col_t col);

/**
 * Does basic parsing of the BMP image (16-Bit 5/6/5 RGB) sent via USART and 
 * sends the image pixels to the display.
 * Image dimensions have to be '(w * h * 2) % 4 = 0' because padded rows 
 * are currently not supported.
 * 
 * @param byte raw BMP byte recieved via USART
 */
void stream(uint8_t byte);

#endif /* BMP_H */

