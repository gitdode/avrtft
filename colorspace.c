/* 
 * File:   colorspace.c
 * Author: torsten.roemer@luniks.net
 *
 * Created on 3. Juli 2024, 19:03
 */

#include "colorspace.h"

void mono1ToRGB16(uint8_t mono, uint8_t *rgb) {
    for (uint8_t i = 0; i < 16; i++) {
        rgb[i] = (mono & (1 << ((15 - i) >> 1))) ? 0x0 : 0xff;
    }
}

void grey4ToRGB16(uint8_t grey, uint8_t *rgb) {
    uint8_t grey4 = ((grey >> 4) & 1);
    uint8_t grey0 = ((grey >> 0) & 1);
    
    rgb[0] = (grey & 0xf0);
    rgb[0] |= (grey4 << 3);
    rgb[0] |= (grey >> 5);

    rgb[1] = ((grey & 0xf0) << 3);
    rgb[1] |= ((grey & 0xf0) >> 3);
    rgb[1] |= (grey4 << 6) | (grey4 << 5) | (grey4 << 0);

    rgb[2] = (grey << 4);
    rgb[2] |= (grey0 << 3);
    rgb[2] |= ((grey & 0x0f) >> 1);

    rgb[3] = (grey << 7);
    rgb[3] |= ((grey & 0x0f) << 1);
    rgb[3] |= (grey0 << 6) | (grey0 << 5) | (grey0 << 0);    
}
