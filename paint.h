/* 
 * File:   paint.h
 * Author: torsten.roemer@luniks.net
 *
 * Created on 29. Dezember 2023, 18:01
 */

#ifndef PAINT_H
#define PAINT_H

#include <stdlib.h>
#include <stdint.h>
#include <math.h>

#include "tft.h"
#include "touch.h"
#include "display.h"

#define CTRL_COUNT 9
#define CTRL_WIDTH DISPLAY_HEIGHT / CTRL_COUNT

/**
 * Initializes and displays the paint application.
 */
void initPaint(void);

/**
 * Handles the given touch event and point.
 * 
 * @param event
 * @param point
 */
void paintEvent(uint8_t event, Point *point);

/**
 * Paints the given point, connecting points with a distance > 1 with
 * a straight line during "contact" touch event.
 * 
 * @param event
 * @param point
 */
void paintPoint(uint8_t event, Point *point);

#endif /* PAINT_H */
