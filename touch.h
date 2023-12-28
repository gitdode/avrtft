/* 
 * File:   touch.h
 * Author: torsten.roemer@luniks.net
 *
 * Created on 12. Dezember 2023, 23:44
 */

#include "types.h"

#ifndef TOUCH_H
#define TOUCH_H

#define FT62XX_WRITE (0x38 << 1) & 0xfe
#define FT62XX_READ  (0x38 << 1) | 0x01

#define T_EVT_PRESS_DOWN    0
#define T_EVT_LIFT_UP       1
#define T_EVT_CONTACT       2
#define T_EVT_NO_EVENT      3

/**
 * Reads the current touch data into the given point and returns the event.
 * 
 * It seems more data is not available; i.e. the gesture always reads 0x00
 * and the weight 0x10.
 * 
 * @param point
 */
uint8_t readTouch(Point *point);

#endif /* TOUCH_H */
