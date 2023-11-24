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
 * Writes the given lines of text to the top left corner of the display.
 * 
 * @param lines text
 * @param length number of lines
 */
void writeError(char *lines[], uint8_t length);

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
 * @param row (8 pixels)
 * @param col (1 pixel)
 * @param font
 * @param code
 * @return glyph width
 */
width_t writeGlyph(row_t row, col_t col, const __flash Font *font, code_t code);

/**
 * Writes the given string with the given font to the given row and column.
 * 
 * @param row (8 pixels)
 * @param col (1 pixel)
 * @param font
 * @param string
 */
void writeString(row_t row, col_t col, const __flash Font *font, const char *string);

/**
 * Displays a demo for the awesome Unifont.
 */
void hackDemo(void);

#endif /* DISPLAY_H */
