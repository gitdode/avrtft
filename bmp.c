/* 
 * File:   bmp.h
 * Author: dode
 * 
 * Thanks to https://en.wikipedia.org/wiki/BMP_file_format
 *
 * Created on 22. November 2023, 23:10
 */

#include "bmp.h"
#include "display.h"
#include "tft.h"
#include "usart.h"
#include "hack.h"

#define BUF_SIZE 4

static bool error = false;

static row_t row = 0;
static col_t col = 0;

static uint8_t buf[BUF_SIZE];
static uint32_t offset = 0;
static uint32_t pixelStart = -1;
static uint32_t pixelEnd = -1;
// static uint32_t headerSize = 0;
static uint32_t bitmapWidth = 0;
static uint32_t bitmapHeight = 0;
static uint16_t bitsPerPixel = 0;
static uint32_t imageSize = 0;
// static uint16_t rowSize = 0;

/**
 * Pushes the given byte on the stack and the oldest off the stack.
 * 
 * @param byte
 */
static void push(uint8_t byte) {
    for (uint8_t i = BUF_SIZE; i-- > 1;) {
        buf[i] = buf[i - 1];
    }
    buf[0] = byte;
}

void prepare(row_t srow, col_t scol) {
    row = srow;
    col = scol;
    offset = 0;
    setStreamingData(true);
}

void stream(uint8_t byte) {
    if (error) {
        // TODO recover from error condition
        // setStreaming(false);
        return;
    }
    push(byte);
    
    if (offset == 0x0 + 1) {
        if (!(buf[1] == 0x42 && buf[0] == 0x4d)) {
            // not a BMP
            // TODO __flash
            char *lines[] = {
                "Not a BMP image or", 
                "transmission error"
            };
            writeError(lines, 2);
            error = true;
            return;
        }
    }
    
    if (offset == 0x0a + 3) {
        pixelStart = 0;
        pixelStart |= ((uint32_t)buf[0]) << 24;
        pixelStart |= ((uint32_t)buf[1]) << 16;
        pixelStart |= buf[2] << 8;
        pixelStart |= buf[3] << 0;
    }
    
    /*
    if (offset == 0x0e + 3) {
        headerSize |= ((uint32_t)buf[0]) << 24;
        headerSize |= ((uint32_t)buf[1]) << 16;
        headerSize |= buf[2] << 8;
        headerSize |= buf[3] << 0;
    }
    */
    
    if (offset == 0x12 + 3) {
        bitmapWidth |= ((uint32_t)buf[0]) << 24;
        bitmapWidth |= ((uint32_t)buf[1]) << 16;
        bitmapWidth |= buf[2] << 8;
        bitmapWidth |= buf[3] << 0;
    }
    
    if (offset == 0x16 + 3) {
        bitmapHeight |= ((uint32_t)buf[0]) << 24;
        bitmapHeight |= ((uint32_t)buf[1]) << 16;
        bitmapHeight |= buf[2] << 8;
        bitmapHeight |= buf[3] << 0;
    }
    
    if (offset == 0x1c + 1) {
        bitsPerPixel |= buf[0] << 8;
        bitsPerPixel |= buf[1] << 0;
        
        if (bitsPerPixel != 16) {
            // not a 16-Bit RGB BMP
            // TODO __flash
            char *lines[] = {
                "Only 16-Bit (5/6/5)", 
                "RGB is supported"
            };
            writeError(lines, 2);
            error = true;
            return;
        }
    }
    
    if (offset == 0x22) {
        imageSize = bitmapWidth * bitmapHeight * bitsPerPixel / 8;
        pixelEnd = pixelStart + imageSize;
        // rowSize = ((bitsPerPixel * bitmapWidth + 31) / 32) * 4;
        uint8_t padding = (bitmapWidth * bitmapHeight * 2) % 4;
        
        if (padding != 0) {
            // row padding currently not supported
            // TODO __flash
            char *lines[] = {
                "Only bitmaps where", 
                "(w * h * 2) % 4 = 0", 
                "are supported"
            };
            writeError(lines, 3);
            error = true;
            return;
        }
    }
    
    if (offset == pixelStart) {
        // do horizontal flip because pixel data in a BMP is bottom to top
        setArea(row, col, bitmapWidth, bitmapHeight, true);
        writeStart();
    }
    
    // TODO calculate number of pad bytes and discard them
    if (offset < pixelEnd && offset >= pixelStart) {
        // swap endianess
        // TODO get rid of division
        if ((offset - pixelStart) % 2) {
            writeByte(buf[0]);
            writeByte(buf[1]);
        }
    }
    
    offset++;
    
    if (offset == pixelEnd) {
        writeEnd();
        setStreamingData(false);
        // printString("write end\r\n");
    }
}