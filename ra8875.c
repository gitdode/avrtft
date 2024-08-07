/* 
 * File:   ra8875.c
 * Author: torsten.roemer@luniks.net
 * 
 * Thanks to https://github.com/adafruit/Adafruit_RA8875
 * for PLL settings and HSync and VSync timings!
 *
 * Created on 1. Juni 2024, 15:33
 */

#if DRIVER == 1

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

/**
 * Sets the cursor to given X and Y coordinates.
 * 
 * @param x
 * @param y
 */
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

/**
 * Sets given background color.
 * 
 * @param color
 */
static void setBackground(uint16_t color) {
    // red
    regWrite(BGCR0, (color & 0xf800) >> 11);
    // green
    regWrite(BGCR1, (color & 0x07e0) >> 5);
    // blue
    regWrite(BGCR2, (color & 0x001f) >> 0);
}

/**
 * Sets given foreground color.
 * 
 * @param color
 */
static void setForeground(uint16_t color) {
    // red
    regWrite(FGCR0, (color & 0xf800) >> 11);
    // green
    regWrite(FGCR1, (color & 0x07e0) >> 5);
    // blue
    regWrite(FGCR2, (color & 0x001f) >> 0);
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
    regWrite(PCSR, 0x80 | 0x01); // 800x480: falling edge, system clock/2
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
    
    uint8_t dpcr = regRead(DPCR);
    if (HFLIP) {
        dpcr |= (1 << 3);
    }
    if (VFLIP) {
        dpcr |= (1 << 2);
    }
    regWrite(DPCR, dpcr);
    
    setActiveWindow(0, 0, DISPLAY_WIDTH - 1, DISPLAY_HEIGHT - 1);
    
    // clear full display
    regWrite(MCLR, 0x80 | 0x00);
    
    _delay_ms(100);
    
    // display on
    regWrite(PWRR, 0x80);
    _delay_ms(20);
    
    // TFT LCD backlight on
    // PWM1
    regWrite(P1CR, 0x80);
    regWrite(P1DCR, 0xff);
    
    // GPIOX write to enable display
    regWrite(GPIOX, 1);
    
    // enable touch panel, wait 16384 clocks, system clock/32
    regWrite(TPCR0, 0x80 | 0x50 | 0x05);
    // do not enable debounce for touch interrupt in auto mode
    regWrite(TPCR1, 0x00);
    // enable touch interrupt
    regWrite(INTC1, 0x04);
    
    spiFast();
    
    printString("done initializing display\r\n");
}

void demoDisplay(void) {
    graphicsMode();
    
    drawPixel(30, 30, 0xffff);
    
    drawCircle( 10,  10,  10, 0xffff);
    drawCircle(790,  10,  10, 0xffff);
    drawCircle( 10, 470,  10, 0xffff);
    drawCircle(790, 470,  10, 0xffff);
    
    drawCircle(200, 240, 30, 0b1111100000000000);
    drawRectangle(370, 210, 60, 60, 0b0000011111100000);
    drawCircle(600, 240, 30, 0b0000000000011111);
    
    textMode();
    
    writeText(350, 300, 0x07e0, 0x0000, "Hello RA8875!");
    
    graphicsMode();
}

void drawPixel(x_t x, y_t y, uint16_t color) {
    setCursor(x, y);
    
    cmdWrite(MRWC);
    displaySel();
    transmit(DATA_WRITE);
    transmit(color >> 8);
    transmit(color);
    displayDes();
    
    waitBusy();
}

void drawCircle(x_t x, y_t y, uint16_t radius, uint16_t color) {
    regWrite(DCHR0, x);
    regWrite(DCHR1, x >> 8);
    
    regWrite(DCVR0, y);
    regWrite(DCVR1, y >> 8);
    
    regWrite(DCRR, radius);
    
    setForeground(color);
    
    regWrite(DCR, 0x40 | 0x20);
    
    waitBusy();
}

void drawRectangle(x_t x, y_t y, width_t width, height_t height, 
                   uint16_t color) {
    regWrite(DLHSR0, x);
    regWrite(DLHSR1, x >> 8);
    
    regWrite(DLVSR0, y);
    regWrite(DLVSR1, y >> 8);
    
    regWrite(DLHER0, x + width - 1);
    regWrite(DLHER1, (x + width - 1) >> 8);
    
    regWrite(DLVER0, y + height - 1);
    regWrite(DLVER1, (y + height - 1) >> 8);
    
    setForeground(color);
    
    regWrite(DCR, 0x80 | 0x20 | 0x10);
    
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
    regWrite(HDBE0, x);
    regWrite(HDBE1, x >> 8);
    
    regWrite(VDBE0, y);
    regWrite(VDBE1, y >> 8); // Bit 7 selects layer
    
    regWrite(BEWR0, width);
    regWrite(BEWR1, width >> 8);
    
    regWrite(BEHR0, height);
    regWrite(BEHR1, height >> 8);
    
    // use BTE function "Solid Fill"
    regWrite(BECR1, 0x0c);
    
    setForeground(color);
    
    regWrite(BECR0, 0x80);
    
    waitBusy();
    
    // reset active window to full screen
    setActiveWindow(0, 0, DISPLAY_WIDTH - 1, DISPLAY_HEIGHT - 1);
}

void setArea(x_t x, y_t y,
             width_t width, height_t height,
             bool hflip, bool vflip) {
    setActiveWindow(x, y, x + width - 1, y + height - 1);
    setCursor(x, y);
    
    uint8_t mwcr2 = regRead(MWCR0);
    if (hflip) {
        mwcr2 |= (1 << 2);
    } else {
        mwcr2 &= ~(1 << 2);
    }
    // vertical flip in memory not possible?
    regWrite(MWCR0, mwcr2);
}

void writeData(const __flash uint8_t *bitmap,
               width_t width, height_t height,
               space_t space) {
    writeStart();    
    writeSpace(bitmap, width, height, space);
    writeEnd();  
}

bool isTouch(void) {
    uint8_t data = regRead(INTC2);

    return data & 0x04;
}

uint8_t readTouch(Point *point) {
    uint8_t tpxh = regRead(TPXH);
    uint8_t tpyh = regRead(TPYH);
    uint8_t tpxyl = regRead(TPXYL);
    
    point->x = (tpxh << 2);
    point->x |= (tpxyl & 0x03);
    
    point->y = (tpyh << 2);
    point->y |= ((tpxyl & 0x0c) >> 2);
    
    // 10-bit ADC
    point->x = ((uint32_t)point->x * DISPLAY_WIDTH) >> 10;
    point->y = ((uint32_t)point->y * DISPLAY_HEIGHT) >> 10;
    
    if (HFLIP) {
        point->x = DISPLAY_WIDTH - point->x;
    }
    if (VFLIP) {
        point->y = DISPLAY_HEIGHT - point->y;
    }
    
    // simple calibration
    point->x = point->x - (DISPLAY_WIDTH / 2 - point->x) / TOUCH_CAL_X;
    point->y = point->y - (DISPLAY_HEIGHT / 2 - point->y) / TOUCH_CAL_Y;
    
    point->x = fmax(0, fmin(DISPLAY_WIDTH - 1, point->x));
    point->y = fmax(0, fmin(DISPLAY_HEIGHT - 1, point->y));
    
    return EVENT_PRESS_DOWN;
}

void clearTouch(void) {
    _delay_ms(10);
    regWrite(INTC2, 0x04);
}

#endif /* DRIVER */