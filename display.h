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

void setFrame(uint8_t byte);

/**
 * Writes the bitmap with the given index to the given row and column 
 * and returns the width of the bitmap.
 * @param row
 * @param col
 * @param index
 * @return bitmap width
 */
width_t writeBitmap(row_t row, col_t col, uint16_t index);

/**
 * Writes the glyph with the given pseudo UTF-8 code point with the given
 * font to the given row and column and returns the width of the glyph.
 * @param row (8 pixels)
 * @param col (1 pixel)
 * @param font
 * @param code
 * @return glyph width
 */
width_t writeGlyph(row_t row, col_t col, const __flash Font *font, code_t code);

/**
 * Writes the given string with the given font to the given row and column.
 * @param row (8 pixels)
 * @param col (1 pixel)
 * @param font
 * @param string
 */
void writeString(row_t row, col_t col, const __flash Font *font, const char *string);

/**
 * Displays a demo for the awesome Unifont.
 */
void unifontDemo(void);

void display(void);

#endif /* DISPLAY_H */