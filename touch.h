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

void readTouch(uint16_t *pos);
