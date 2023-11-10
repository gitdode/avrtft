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
#include "unifont.h"
#include "dejavu.h"
#include "bitmaps.h"
#include "spi.h"
#include "tft.h"
#include "usart.h"
#include "utils.h"

static void bufferBitmap(row_t row, col_t col,
                         const __flash uint8_t *bitmap,
                         width_t width, height_t height) {
    
}

void setFrame(uint8_t byte) {
    
}

width_t writeBitmap(row_t row, col_t col, uint16_t index) {
    const __flash Bitmap *bitmap = &bitmaps[index];
    bufferBitmap (row, col, bitmap->bitmap, bitmap->width, bitmap->height);
    
    return bitmap->width;
}

width_t writeGlyph(row_t row, col_t col, const __flash Font *font, code_t code) {
    const __flash Glyph *glyph = getGlyphAddress(font, code);
    bufferBitmap(row, col, glyph->bitmap, glyph->width, font->height);
    
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

void unifontDemo(void) {
//    const __flash Font *unifont = &unifontFont;
//    
//    for (uint8_t i = 0; i < UNIFONT_DEMO_SIZE; i++) {
//        const __flash char *line = demoTextLines[i];
//        char buf[UNIFONT_DEMO_LINE_SIZE];
//        strncpy_P(buf, line, UNIFONT_DEMO_LINE_SIZE - 1);
//        writeString(i * 2, 0, unifont, buf);
//    }
}

void display() {
    initDisplay();
    updateDisplay();
}
