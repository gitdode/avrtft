/* 
 * File:   touch.c
 * Author: torsten.roemer@luniks.net
 *
 * Created on 12. Dezember 2023, 23:44
 */

#include <avr/interrupt.h>
#include "touch.h"
#include "i2c.h"
#include "usart.h"

void readTouch(uint16_t *point) {
    i2cStart();
    i2cSend(FT62XX_WRITE);
    // start reading at TD_STATUS
    i2cSend(0x02);

    i2cStart();
    i2cSend(FT62XX_READ);

    // TD_STATUS
    uint8_t tdStatus = i2cReadAck();
    point[0] |= (tdStatus & 0x0f);

    // P1_X
    uint8_t xh = i2cReadAck();
    uint8_t xl = i2cReadAck();
    point[1] |= (xh & 0x0f) << 8;
    point[1] |= xl;

    // P1_Y
    uint8_t yh = i2cReadAck();
    uint8_t yl = i2cReadNack();
    point[2] |= (yh & 0x0f) << 8;
    point[2] |= yl;

    i2cStop();
}