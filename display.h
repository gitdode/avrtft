/* 
 * File:   display.h
 * Author: torsten.roemer@luniks.net
 *
 * Created on 18. April 2023, 21:56
 */

#ifndef DISPLAY_H
#define DISPLAY_H

#include "types.h"
#include "bitmaps.h"
#include "font.h"

/**
 * Sets the whole display to the given 16-Bit (5/6/5) RGB color.
 * 
 * @param color
 */
void setFrame(uint16_t color);

/**
 * Draws a rectangle with the given origin and dimensions, line thickness
 * and color.
 * 
 * @param row
 * @param col
 * @param width
 * @param height
 * @param thickness
 * @param color
 */
void drawRectangle(row_t row, col_t col, width_t width, height_t height, 
                   uint8_t thickness, uint16_t color);

/**
 * Writes the bitmap with the given index to the given row and column 
 * and returns the width of the bitmap.
 * 
 * @param row
 * @param col
 * @param index
 * @return bitmap width
 */
width_t writeBitmap(row_t row, col_t col, uint16_t index);

/**
 * Writes the glyph with the given pseudo UTF-8 code point with the given
 * font to the given row and column and returns the width of the glyph.
 * 
 * @param row
 * @param col
 * @param font
 * @param code
 * @return glyph width
 */
width_t writeGlyph(row_t row, col_t col, const __flash Font *font, code_t code);

/**
 * Writes the given string with the given font to the given row and column.
 * 
 * @param row
 * @param col
 * @param font
 * @param string
 */
void writeString(row_t row, col_t col, const __flash Font *font, const char *string);

/**
 * Writes the given lines of text to the top left corner of the display.
 * 
 * @param lines text
 * @param length number of lines
 */
void writeError(char *lines[], uint8_t length);

/**
 * Displays a demo for the nice Hack font.
 */
void hackDemo(void);

#endif /* DISPLAY_H */
