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

void readTouch(uint16_t *pos) {
    i2cStart();
    i2cSend(FT62XX_WRITE);
    i2cSend(0x03);

    i2cStart();
    i2cSend(FT62XX_READ);
    uint8_t xh = i2cReadAck();
    uint8_t xl = i2cReadAck();
    uint8_t yh = i2cReadAck();
    uint8_t yl = i2cReadNack();
    i2cStop();

    pos[0] |= (xh & 0x0f) << 8;
    pos[0] |= xl;

    pos[1] |= (yh & 0x0f) << 8;
    pos[1] |= yl;
}