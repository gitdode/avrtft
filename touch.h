/* 
 * File:   touch.h
 * Author: torsten.roemer@luniks.net
 *
 * Created on 12. Dezember 2023, 23:44
 */

#ifndef TOUCH_H
#define TOUCH_H

#define FT62XX_WRITE (0x38 << 1) & 0xfe
#define FT62XX_READ  (0x38 << 1) | 0x01

#endif /* TOUCH_H */

/**
 * Reads the current touch data into the given array:
 * 0: number of touch points: 0 or 1
 * 1: touch point X position
 * 2: touch point Y position
 * 
 * It seems more data is not available; i.e. the gesture always reads 0x00
 * and the weight 0x10.
 * 
 * @param point array with appropriate length
 */
void readTouch(uint16_t *point);
