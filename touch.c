/* 
 * File:   touch.c
 * Author: torsten.roemer@luniks.net
 *
 * Created on 12. Dezember 2023, 23:44
 */

#include <avr/interrupt.h>
#include "touch.h"
#include "i2c.h"
#include "tft.h"
#include "usart.h"

uint8_t readTouch(Point *point) {
    i2cStart();
    i2cSend(FT62XX_WRITE);
    // start reading at P1_XH
    i2cSend(0x03);

    i2cStart();
    i2cSend(FT62XX_READ);

    // TD_STATUS
    // uint8_t tdStatus = i2cReadAck();
    // tdStatus = (tdStatus & 0x0f);

    // P1_X
    uint8_t xh = i2cReadAck();
    uint8_t xl = i2cReadAck();
    uint8_t eventFlag = (xh & 0xc0) >> 6;
    // swapping x and y according to display's row/column exchange default
    point->y = (xh & 0x0f) << 8;
    point->y |= xl;

    // P1_Y
    uint8_t yh = i2cReadAck();
    uint8_t yl = i2cReadNack();
    // swapping x and y according to display's row/column exchange default
    point->x = (yh & 0x0f) << 8;
    point->x |= yl;

    i2cStop();

    if (!VFLIP) {
        point->x = DISPLAY_WIDTH - point->x;
    }
    if (HFLIP) {
        point->y = DISPLAY_HEIGHT - point->y;
    }

    return eventFlag;
}
