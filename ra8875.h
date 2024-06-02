/* 
 * File:   ra8875.h
 * Author: torsten.roemer@luniks.net
 *
 * Created on 1. Juni 2024, 15:32
 */

#ifndef RA8875_H
#define RA8875_H

#include "types.h"
#include "pins.h"
#include "usart.h"
#include "spi.h"

#define CMD_WRITE   0x80
#define STATUS_READ 0xc0
#define DATA_WRITE  0x00
#define DATA_READ   0x40

/* System & Configuration Registers */
#define PWRR    0x01
#define MRWC    0x02
#define PCSR    0x04
#define SYSR    0x10

/* Horizontal (Sync) Registers */
#define HDWR    0x14
#define HNDFTR  0x15
#define HNDR    0x16
#define HSTR    0x17
#define HPWR    0x18

/* Vertical (Sync) Registers */
#define VDHR0   0x19
#define VDHR1   0x1a
#define VNDR0   0x1b
#define VNDR1   0x1c
#define VSTR0   0x1d
#define VSTR1   0x1e
#define VPWR    0x1f

/* LCD Display Control Registers */
#define DPCR    0x20
#define FNCR0   0x21
#define FNCR1   0x22
#define F_CURXL 0x2a
#define F_CURXH 0x2b
#define F_CURYL 0x2c
#define F_CURYH 0x2d

/* Active Window & Scroll Window Setting Registers */
#define HSAW0   0x30
#define HSAW1   0x31
#define VSAW0   0x32
#define VSAW1   0x33
#define HEAW0   0x34
#define HEAW1   0x35
#define VEAW0   0x36
#define VEAW1   0x37

/* Cursor Setting Registers */
#define MWCR0   0x40
#define CURH0   0x46
#define CURH1   0x47
#define CURV0   0x48
#define CURV1   0x49

/* Background Color Registers */
#define BGCR0   0x60
#define BGCR1   0x61
#define BGCR2   0x62

/* Foreground Color Registers */
#define FGCR0   0x63
#define FGCR1   0x64
#define FGCR2   0x65

/* PLL Setting Registers */
#define PLLC1   0x88
#define PLLC2   0x89

/*  PWM Control Registers */
#define P1CR    0x8a
#define P1DCR   0x8b

/* Memory Clear Control Register */
#define MCLR    0x8e

/* Drawing Contol Registers */
#define DCR     0x90
#define DCHR0   0x99
#define DCHR1   0x9a
#define DCVR0   0x9b
#define DCVR1   0x9c
#define DCRR    0x9d

/*  Key & IO Control Registers */
#define GPIOX   0xc7

#ifndef DISPLAY_WIDTH
    #define DISPLAY_WIDTH   800
#endif

#ifndef DISPLAY_HEIGHT
    #define DISPLAY_HEIGHT  480
#endif

/* HSync + VSync currently only for 800x480 */
#define HNDFT   0
#define HNDP    10 
#define HSP     32
#define HPW     96

#define VNDP    32
#define VSP     23
#define VPW     2

#ifndef BGR
    #define BGR     0
#endif

#ifndef INVERT
    #define INVERT  0
#endif

#ifndef HFLIP
    #define HFLIP   0
#endif

#ifndef VFLIP
    #define VFLIP   0
#endif

// TODO use enum? typedef?
#define SPACE_MONO1  1
#define SPACE_GREY4  4
#define SPACE_RGB16  16

/**
 * Initializes the display.
 */
void initDisplay(void);

/**
 * Just a test.
 */
void ra8875Test(void);

/**
 * Sets given background color.
 * 
 * @param color
 */
void setBackground(uint16_t color);

/**
 * Sets given foreground color.
 * 
 * @param color
 */
void setForeground(uint16_t color);

/**
 * Draws a pixel at given coordinates and color.
 * 
 * @param x
 * @param y
 * @param color
 */
void drawPixel(uint16_t x, uint16_t y, uint16_t color);

/**
 * Draws a circle at given center coordinates, radius and color.
 * 
 * @param x
 * @param y
 * @param radius
 * @param color
 */
void drawCircle(uint16_t x, uint16_t y, uint16_t radius, uint16_t color);

/**
 * Writes given text at given coordinates and foreground and background color.
 * 
 * @param x
 * @param y
 * @param fg
 * @param bg
 * @param string
 */
void writeText(uint16_t x, uint16_t y, uint16_t fg, uint16_t bg, char *string);

/**
 * Sets to write data to display RAM.
 */
void writeStart(void);

/**
 * Writes the given byte to display RAM.
 * 
 * @param byte
 */
void writeByte(uint8_t byte);

/**
 * Completes writing data to display RAM.
 */
void writeEnd(void);

/**
 * Sets the given color in the given area of the display.
 * 
 * @param row row in pixels, origin top left
 * @param col column in pixels, origin top left
 * @param width width in pixels
 * @param height height in pixels
 * @param color 16-Bit (5/6/5) RGB color
 */
void fillArea(row_t row, col_t col,
              width_t width, height_t height,
              uint16_t color);

/**
 * Sets the area to write image data to.
 * 
 * @param row row in pixels, origin top left
 * @param col column in pixels, origin top left
 * @param width width of the bitmap in pixels
 * @param height height of the bitmap in pixels
 * @param hflip if image should be flipped horizontally
 * @param vflip if image should be flipped vertically
 */
void setArea(row_t row, col_t col,
             width_t width, height_t height,
             bool hflip, bool vflip);

/**
 * Writes image data to the previously set area.
 * 
 * @param bitmap pointer to bitmap data in program memory
 * @param width width of the bitmap in pixels
 * @param height height of the bitmap in pixels
 * @param space color space of the bitmap
 */
void writeData(const __flash uint8_t *bitmap,
               width_t width, height_t height,
               space_t space);

#endif /* RA8875_H */
