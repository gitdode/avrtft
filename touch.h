/* 
 * File:   touch.h
 * Author: torsten.roemer@luniks.net
 *
 * Created on 12. Dezember 2023, 23:44
 */

#include <avr/interrupt.h>
#include "types.h"
#include "i2c.h"
#include "tft.h"
#include "usart.h"

#ifndef TOUCH_H
#define TOUCH_H

#define FT62XX_WRITE (0x38 << 1) & 0xfe
#define FT62XX_READ  (0x38 << 1) | 0x01

#define EVENT_PRESS_DOWN    0
#define EVENT_LIFT_UP       1
#define EVENT_CONTACT       2
#define EVENT_NO_EVENT      3

/**
 * Returns true if there was a touch event, false otherwise.
 * 
 * @return true if touch event
 */
bool isTouch(void);

/**
 * Reads the current touch position into the given point and returns 
 * the touch event.
 * 
 * It seems more data than that (besides the touch count) is not available; 
 * i.e. the gesture always reads 0x00 and the weight 0x10.
 * 
 * @param point touch position
 * @return touch event
 */
uint8_t readTouch(Point *point);

/**
 * Clears the touch event.
 */
void clearTouch(void);

#endif /* TOUCH_H */
