/* 
 * File:   ra8875.c
 * Author: torsten.roemer@luniks.net
 * 
 * Thanks to https://github.com/adafruit/Adafruit_RA8875
 * for PLL settings and HSync and VSync timings!
 *
 * Created on 1. Juni 2024, 15:33
 */

#include <util/delay.h>

#include "ra8875.h"

/**
 * Does a hardware reset.
 */
static void hwReset(void) {
    PORT_DISP &= ~(1 << PIN_RST);
    _delay_ms(10);
    PORT_DISP |= (1 << PIN_RST);
    _delay_ms(100);
}

/**
 * Waits until the display is no longer busy.
 */
static void waitBusy(void) {
    loop_until_bit_is_set(PINP_DISP, PIN_BUSY);
}

/**
 * Writes given command to controller.
 * 
 * @param cmd
 */
static void cmdWrite(uint8_t cmd) {
    displaySel();
    transmit(CMD_WRITE);
    transmit(cmd);
    displayDes();
}

/**
 * Reads status of controller.
 * 
 * @return status
 */
static uint8_t statusRead(void) {
    displaySel();
    transmit(STATUS_READ);
    uint8_t status = transmit(0x00);
    displayDes();
    
    return status;
}

/**
 * Writes given data to controller.
 * 
 * @param data
 */
static void dataWrite(uint8_t data) {
    displaySel();
    transmit(DATA_WRITE);
    transmit(data);
    displayDes();
}

/**
 * Reads data from controller.
 * 
 * @return data
 */
static uint8_t dataRead(void) {
    displaySel();
    transmit(DATA_READ);
    uint8_t data = transmit(0x00);
    displayDes();
    
    return data;
}

/**
 * Writes given data to given register.
 * 
 * @param reg
 * @param data
 */
static void regWrite(uint8_t reg, uint8_t data) {
    cmdWrite(reg);
    dataWrite(data);
}

/**
 * Reads data from given register and returns it.
 * 
 * @param reg
 * @return data
 */
static uint8_t regRead(uint8_t reg) {
    cmdWrite(reg);
    return dataRead();
}

/**
 * Sets the window in that to write text, draw graphics or write to memory.
 * The cursor must be set to the start coordinates of the window.
 * 
 * @param xs X start
 * @param ys Y start
 * @param xe X end
 * @param ye Y end
 */
static void setActiveWindow(x_t xs, y_t ys, x_t xe, y_t ye) {
    // horizontal start point of active window
    regWrite(HSAW0, xs);
    regWrite(HSAW1, xs >> 8);
    
    // vertical start point of active window
    regWrite(VSAW0, ys);
    regWrite(VSAW1, ys >> 8);
    
    // horizontal end point of active window
    regWrite(HEAW0, xe);
    regWrite(HEAW1, xe >> 8);
    
    // vertical end point of active window
    regWrite(VEAW0, ye);
    regWrite(VEAW1, ye >> 8);
}

static void setCursor(x_t x, y_t y) {
    regWrite(CURH0, x);
    regWrite(CURH1, x >> 8);
    
    regWrite(CURV0, y);
    regWrite(CURV1, y >> 8);
}

/**
 * Switches to graphics mode.
 */
static void graphicsMode(void) {
    uint8_t data = regRead(MWCR0);
    data &= ~(1 << 7);
    regWrite(MWCR0, data);
}

/**
 * Switches to text mode.
 */
static void textMode(void) {
    uint8_t data = regRead(MWCR0);
    data |= (1 << 7);
    regWrite(MWCR0, data);
}

void initDisplay(void) {
    spiSlow();
    
    hwReset();
    
    // set wake up
    // cmdWrite(PWRR);
    // dataWrite(0x00);
    // _delay_ms(100);
    
    // set PLL
    regWrite(PLLC1, 0x00 + 11); // 800x480: 11
    _delay_ms(1);
    regWrite(PLLC2, 0x02); // div by 4
    _delay_ms(1);
    
    // set pixel clock
    regWrite(PCSR, 0x80 | 0x01); // 800x480: falling edge, 2 times system clock
    _delay_ms(20);
    
    // set 16-bit color depth, 8-bit MCU
    regWrite(SYSR, 0x0c | 0x00);
    
    // display width
    regWrite(HDWR, DISPLAY_WIDTH / 8 - 1);
    
    // horizontal sync
    regWrite(HNDFTR, 0x00 + HNDFT);
    regWrite(HNDR, (HNDP - HNDFT - 2) / 8);
    regWrite(HSTR, HSP / 8 - 1);
    regWrite(HPWR, 0x00 + (HPW / 8 - 1));
    
    // display height
    regWrite(VDHR0, (uint8_t)(DISPLAY_HEIGHT - 1));
    regWrite(VDHR1, DISPLAY_HEIGHT >> 8);
    
    // vertical sync
    regWrite(VNDR0, VNDP - 1);
    regWrite(VNDR1, VNDP >> 8);
    regWrite(VSTR0, VSP - 1);
    regWrite(VSTR1, VSP >> 8);
    regWrite(VPWR, 0x00 + VPW - 1);
    
    setActiveWindow(0, 0, DISPLAY_WIDTH - 1, DISPLAY_HEIGHT - 1);
    
    // clear full display
    regWrite(MCLR, 0x80 | 0x00);
    
    _delay_ms(100);
    
    // display on
    regWrite(PWRR, 0x80);
    _delay_ms(20);
    
    spiFast();
    
    // TFT LCD backlight on
    // PWM1
    regWrite(P1CR, 0x80);
    regWrite(P1DCR, 0xff);
    
    // GPIOX write to enable display
    regWrite(GPIOX, 1);
    
    // enable touch panel
    regWrite(TPCR0, 0x80);
    // enable touch interrupt
    regWrite(INTC1, 0x04);
    
    printString("done initializing display\r\n");
}

void ra8875Test(void) {
    graphicsMode();
    
    drawPixel(30, 30, 0xffff);
    
    drawCircle( 10,  10,  10, 0xffff);
    drawCircle(790,  10,  10, 0xffff);
    drawCircle( 10, 470,  10, 0xffff);
    drawCircle(790, 470,  10, 0xffff);
    
    drawCircle(200, 240, 30, 0b1111100000000000);
    drawCircle(400, 240, 30, 0b0000011111100000);
    drawCircle(600, 240, 30, 0b0000000000011111);
    
    textMode();
    
    writeText(350, 300, 0x07e0, 0x0000, "Hello RA8875!");
}

void setBackground(uint16_t color) {
    // red
    regWrite(BGCR0, (color & 0xf800) >> 11);
    // green
    regWrite(BGCR1, (color & 0x07e0) >> 5);
    // blue
    regWrite(BGCR2, (color & 0x001f) >> 0);
}

void setForeground(uint16_t color) {
    // red
    regWrite(FGCR0, (color & 0xf800) >> 11);
    // green
    regWrite(FGCR1, (color & 0x07e0) >> 5);
    // blue
    regWrite(FGCR2, (color & 0x001f) >> 0);
}

void drawPixel(x_t x, y_t y, uint16_t color) {
    regWrite(CURH0, x);
    regWrite(CURH1, x >> 8);
    
    regWrite(CURV0, y);
    regWrite(CURV1, y >> 8);
    
    cmdWrite(MRWC);
    displaySel();
    transmit(DATA_WRITE);
    transmit(color >> 8);
    transmit(color);
    displayDes();
    
    waitBusy();
}

void drawCircle(x_t x, y_t y, uint16_t radius, uint16_t color) {
    // set the center of the circle
    regWrite(DCHR0, x);
    regWrite(DCHR1, x >> 8);
    
    regWrite(DCVR0, y);
    regWrite(DCVR1, y >> 8);
    
    // set the radius of the circle
    regWrite(DCRR, radius);
    
    // set the color of the circle
    setForeground(color);
    
    // start circle drawing function
    regWrite(DCR, 0x40 | 0x20);
    
    waitBusy();
}

void writeText(x_t x, y_t y, uint16_t fg, uint16_t bg, char *string) {
    regWrite(F_CURXL, x);
    regWrite(F_CURXH, x >> 8);
    
    regWrite(F_CURYL, y);
    regWrite(F_CURYH, y >> 8);
    
    setForeground(fg);
    setBackground(bg);
    
    cmdWrite(MRWC);
    for (; *string != '\0'; string++) {
        dataWrite(*string);
    }
}

void writeStart(void) {
    cmdWrite(MRWC);
    displaySel();
    transmit(DATA_WRITE);
}

void writeRestart(void) {
    cmdWrite(MRWC);
    displaySel();
    transmit(DATA_WRITE);
}

void writeByte(uint8_t byte) {
    transmit(byte);
}

void writeEnd(void) {
    displayDes();
    waitBusy();
}

void fillArea(x_t x, y_t y,
              width_t width, height_t height,
              uint16_t color) {
    
}

void setArea(x_t x, y_t y,
             width_t width, height_t height,
             bool hflip, bool vflip) {
    setActiveWindow(x, y, x + width - 1, y + height - 1);
    graphicsMode();
    
    uint8_t dpcr = regRead(DPCR);
    // hflip not possible?
    if (hflip) {
        dpcr |= (1 << 2);
    } else {
        dpcr &= ~(1 << 2);
    }
    regWrite(DPCR, dpcr);
    
    uint8_t mwcr2 = regRead(MWCR0);
    if (vflip) {
        mwcr2 |= (1 << 2);
    } else {
        mwcr2 &= ~(1 << 2);
    }
    regWrite(MWCR0, mwcr2);
    
    setCursor(x, y);
}

void writeData(const __flash uint8_t *bitmap,
               width_t width, height_t height,
               space_t space) {
    
}

#if DRIVER == RA8875

bool isTouch(void) {
    uint8_t data = regRead(INTC2);

    return data & 0x04;
}

uint8_t readTouch(Point *point) {
    // TODO implement
    return 0;
}

void clearTouch(void) {
    regWrite(INTC2, 0x04);
}

#endif /* DRIVER */