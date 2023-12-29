/* 
 * File:   draw.h
 * Author: torsten.roemer@luniks.net
 *
 * Created on 29. Dezember 2023, 18:01
 */

#ifndef DRAW_H
#define DRAW_H

#include <stdlib.h>
#include <stdint.h>
#include <math.h>

#include "tft.h"
#include "touch.h"

void draw(uint8_t event, Point *point, uint16_t color, uint8_t thickness);

#endif /* DRAW_H */

