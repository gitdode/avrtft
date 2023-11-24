/* 
 * File:   display.h
 * Author: torsten.roemer@luniks.net
 *
 * Created on 18. April 2023, 21:56
 */

#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <avr/pgmspace.h>
#include "display.h"
#include "hack.h"
#include "dejavu.h"
#include "bitmaps.h"
#include "spi.h"
#include "tft.h"
#include "usart.h"
#include "utils.h"

void setFrame(uint16_t color) {
    fillArea(0, 0, DISPLAY_WIDTH, DISPLAY_HEIGHT, color);
}

width_t writeBitmap(row_t row, col_t col, uint16_t index) {
    const __flash Bitmap *bitmap = &bitmaps[index];
    setArea(row, col, bitmap->width, bitmap->height, false);
    writeData(bitmap->bitmap, bitmap->width, bitmap->height, SPACE_RGB16);
    
    return bitmap->width;
}

width_t writeGlyph(row_t row, col_t col, const __flash Font *font, code_t code) {
    const __flash Glyph *glyph = getGlyphAddress(font, code);
    // TODO handle DejaVu font with 1-Bit B/W colors
    setArea(row, col, glyph->width, font->height, false);
    writeData(glyph->bitmap, glyph->width, font->height, SPACE_GREY4);
    
    return glyph->width;
}

void writeString(row_t row, col_t col, const __flash Font *font, const char *string) {
    uint8_t offset = 0;
    for (; *string != '\0'; string++) {
        uint8_t c = (uint8_t) *string;
        if (c == 194) {
            // multibyte
        } else if (c == 195) {
            // multibyte, add 64 to get code point
            offset = 64;
        } else {
            code_t code = c + offset;
            col += writeGlyph(row, col, font, code);
            offset = 0;
        }
    }
}

void hackDemo(void) {
    const __flash Font *hack = &hackFont;
    
    for (uint8_t i = 0; i < HACK_DEMO_SIZE; i++) {
        const __flash char *line = demoTextLines[i];
        char buf[HACK_DEMO_LINE_SIZE];
        strlcpy_P(buf, line, HACK_DEMO_LINE_SIZE - 1);
        writeString(i * hack->height, 0, hack, buf);
    }
}
