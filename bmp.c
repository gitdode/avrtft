/* 
 * File:   bmp.h
 * Author: dode
 *
 * Created on 22. November 2023, 23:10
 */

#include "bmp.h"
#include "tft.h"
#include "usart.h"

#define BUF_SIZE 4

static row_t row;
static col_t col;

static uint32_t buf[BUF_SIZE];
static uint32_t offset = 0;
static uint32_t pixelStart = 0;
static uint32_t pixelEnd = 0;
static uint32_t headerSize = 0;
static uint32_t bitmapWidth = 0;
static uint32_t bitmapHeight = 0;
static uint16_t bitsPerPixel = 0;
static uint32_t imageSize = 0;
static uint16_t rowSize = 0;

static void push(uint8_t byte) {
    for (uint8_t i = BUF_SIZE; i-- > 1;) {
        buf[i] = buf[i - 1];
    }
    buf[0] = byte;
}

// TODO how to do in C?
void prepare(row_t srow, col_t scol) {
    row = srow;
    col = scol;
    offset = 0;
    setStreaming(true);
}

void stream(uint8_t byte) {
    // printByte(byte);
    // char buf[16];
    // snprintf(buf, sizeof (buf), "%ld\r\n", offset);
    // printString(buf);
    
    push(byte);
    
    if (offset == 0x0 + 1) {
        if (buf[1] == 0x42 && buf[0] == 0x4d) {
            // printString("this is a BMP\r\n");
        } else {
            // printString("this is not a BMP\n");
        }
    }
    
    if (offset == 0x0a + 3) {
        pixelStart = buf[0] << 24;
        pixelStart = buf[1] << 16;
        pixelStart = buf[2] << 8;
        pixelStart = buf[3] << 0;
        
        // printf("pixel start is at offset: %ld\n", pixelStart);
//        char string[64];
//        snprintf(string, sizeof (string), "pixel start: %ld\r\n", pixelStart);
//        printString(string);
    }
    
    if (offset == 0x0e + 3) {
        headerSize = buf[0] << 24;
        headerSize = buf[1] << 16;
        headerSize = buf[2] << 8;
        headerSize = buf[3] << 0;
        
        // printf("header size: %ld\n", headerSize);
//        char string[64];
//        snprintf(string, sizeof (string), "header size: %ld\r\n", headerSize);
//        printString(string);
    }
    
    if (offset == 0x12 + 3) {
        bitmapWidth = buf[0] << 24;
        bitmapWidth = buf[1] << 16;
        bitmapWidth = buf[2] << 8;
        bitmapWidth = buf[3] << 0;
        
        // printf("bitmap width: %ld\n", bitmapWidth);
//        char string[64];
//        snprintf(string, sizeof (string), "bitmap width: %ld\r\n", bitmapWidth);
//        printString(string);
    }
    
    if (offset == 0x16 + 3) {
        bitmapHeight = buf[0] << 24;
        bitmapHeight = buf[1] << 16;
        bitmapHeight = buf[2] << 8;
        bitmapHeight = buf[3] << 0;
        
        // printf("bitmap height: %ld\n", bitmapHeight);
//        char string[64];
//        snprintf(string, sizeof (string), "bitmap height: %ld\r\n", bitmapHeight);
//        printString(string);
    }
    
    if (offset == 0x1c + 1) {
        bitsPerPixel = buf[0] << 8;
        bitsPerPixel = buf[1] << 0;
        
        // printf("bits per pixel: %ld\n", bitsPerPixel);
//        char string[64];
//        snprintf(string, sizeof (string), "bits per pixel: %d\r\n", bitsPerPixel);
//        printString(string);
    }
    
    if (offset == 0x22) {
        imageSize = bitmapWidth * bitmapHeight * bitsPerPixel / 8;
        pixelEnd = pixelStart + imageSize;
        // rowSize = ((bitsPerPixel * bitmapWidth + 31) / 32) * 4;
        
        // printf("image size: %ld\n", imageSize);
        // printf("pixel end is at offset: %ld\n", pixelEnd);
        // printf("row size: %ld\n", rowSize);
//        char string[64];
//        snprintf(string, sizeof (string), "image size: %ld, pixel end: %ld\r\n", imageSize, pixelEnd);
//        printString(string);
    }
    
    if (offset == pixelStart) {
        setArea(row, col, bitmapWidth, bitmapHeight, true);
        writeStart();
        // printString("write start\r\n");        
    }
    
    // TODO calculate number of pad bytes and discard them
    if (offset < pixelEnd && offset >= pixelStart) {
        // swap endianess
        if ((offset - pixelStart) % 2) {
            // printf("0x%02x, ", buf[0]);
            // printf("0x%02x, ", buf[1]);
            // if ((offset - pixelStart) % 16 == 15) {
            //     putchar('\n');  // 16 bytes per line
            // }
            
            // printByte(buf[0]);
            // printByte(buf[1]);
            writeByte(buf[0]);
            writeByte(buf[1]);
        }
    }
    
    offset++;
    
    if (offset > 0 && offset == pixelEnd) {
        writeEnd();
        printString("write end\r\n");
    }
}