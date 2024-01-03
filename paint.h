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

#define CTRL_COUNT      9
#define TOOL_COUNT      6
#define BITMAP_PADDING  5
#define CTRL_WIDTH DISPLAY_HEIGHT / CTRL_COUNT

#define TOOL_FREE       0
#define TOOL_LINE       1
#define TOOL_RECT       2
#define TOOL_ERASER     3
#define TOOL_THICK      4
#define TOOL_CLEAR      5

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
 * a straight line during "contact" touch event or draws a rectangle.
 * 
 * @param event
 * @param point
 */
void paintPoint(uint8_t event, Point *point);

#endif /* PAINT_H */
