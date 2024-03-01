/* 
 * File:   bmp.h
 * Author: torsten.roemer@luniks.net
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
 * Resets the state.
 */
static void reset(void) {
    offset = 0;
    pixelStart = -1;
    pixelEnd = -1;
    // headerSize = 0;
    bitmapWidth = 0;
    bitmapHeight = 0;
    bitsPerPixel = 0;
    imageSize = 0;
    // rowSize = 0;
}

/**
 * Pushes the given byte on the queue and the oldest off the queue,
 * LSB at the smallest index/address.
 * 
 * @param byte
 */
static void push(uint8_t byte) {
    for (uint8_t i = 0; i < BUF_SIZE - 1; i++) {
        buf[i] = buf[i + 1];
    }
    buf[BUF_SIZE - 1] = byte;
}

void prepare(row_t srow, col_t scol) {
    row = srow;
    col = scol;
    offset = 0;
    setStreamingData(true);
}

uint8_t stream(uint8_t byte) {
    if (error) {
        // TODO recover from error condition
        // setStreaming(false);
        return BMP_ERROR;
    }
    push(byte);
    
    if (offset == 0x0 + 1) {
        if (!(buf[2] == 0x42 && buf[3] == 0x4d)) {
            // not a BMP
            // TODO __flash
            char *lines[] = {
                "Not a BMP image or", 
                "transmission error"
            };
            writeError(lines, 2);
            error = true;
            return BMP_ERROR;
        }
    }
    
    if (offset == 0x0a + 3) {
        memcpy(&pixelStart, &buf, sizeof (pixelStart));
    }
    
    /*
    if (offset == 0x0e + 3) {
        memcpy(&headerSize, &buf, 4);
    }
    */
    
    if (offset == 0x12 + 3) {
        memcpy(&bitmapWidth, &buf, sizeof (bitmapWidth));
    }
    
    if (offset == 0x16 + 3) {
        memcpy(&bitmapHeight, &buf, sizeof (bitmapHeight));
    }
    
    if (offset == 0x1c + 1) {
        memcpy(&bitsPerPixel, &buf[2], sizeof (bitsPerPixel));
        
        if (bitsPerPixel != 16) {
            // not a 16-Bit RGB BMP
            // TODO __flash
            char *lines[] = {
                "Only 16-Bit (5/6/5)", 
                "RGB is supported"
            };
            writeError(lines, 2);
            error = true;
            return BMP_ERROR;
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
            return BMP_ERROR;
        }
    }
    
    if (offset == pixelStart) {
        // do horizontal flip because pixel data in a BMP is bottom to top
        setArea(row, col, bitmapWidth, bitmapHeight, true, false);
        writeStart();
    }
    
    // TODO calculate number of pad bytes and discard them
    if (offset < pixelEnd && offset >= pixelStart) {
        // no expensive division done since modulo is a power of 2
        if ((offset - pixelStart) % 2) {
            writeByte(buf[3]);
            writeByte(buf[2]);
        }
    }
    
    offset++;
    
    if (offset == pixelEnd) {
        writeEnd();
        reset();
        setStreamingData(false);
        // printString("write end\r\n");
        
        return BMP_READY;
    }
    
    return BMP_BUSY;
}

void readSD(uint32_t address) {
    prepare(0, 0);
    uint8_t block[SD_BLOCK_SIZE];
    uint8_t status;
    do {
        displayDes();
        bool success = readSingleBlock(address++, block);
        displaySel();
        if (success) {
            for (uint16_t j = 0; j < SD_BLOCK_SIZE && status == BMP_BUSY; j++) {
                status = stream(block[j]);
            }
        }
    } while (status == BMP_BUSY);
}