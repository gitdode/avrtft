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
 * @param x
 * @param y
 * @param width
 * @param height
 * @param thickness
 * @param color
 */
void drawRectangle(x_t x, y_t y, width_t width, height_t height, 
                   uint8_t thickness, uint16_t color);

/**
 * Writes the bitmap with the given index to the given row and column 
 * and returns the width of the bitmap.
 * 
 * @param x
 * @param y
 * @param index
 * @return bitmap width
 */
width_t writeBitmap(x_t x, y_t y, uint16_t index);

/**
 * Writes the glyph with the given pseudo UTF-8 code point with the given
 * font to the given row and column and returns the width of the glyph.
 * 
 * @param x
 * @param y
 * @param font
 * @param code
 * @return glyph width
 */
width_t writeGlyph(x_t x, y_t y, const __flash Font *font, code_t code);

/**
 * Writes the given string with the given font to the given row and column.
 * 
 * @param x
 * @param y
 * @param font
 * @param string
 */
void writeString(x_t x, y_t y, const __flash Font *font, const char *string);

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
