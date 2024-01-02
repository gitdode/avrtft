/* 
 * File:   paint.c
 * Author: torsten.roemer@luniks.net
 *
 * Created on 29. Dezember 2023, 18:01
 */

#include "paint.h"
#include "usart.h"

static uint16_t colors[] = {
    0xf800, 0x07e0, 0x001f, 
    0xffe0, 0xf81f, 0x07ff, 
    0x0000, 0xe71c, 0xffff};

static uint8_t tool = TOOL_FREEHAND;
static Point prev = {0};
static uint16_t color = 0x0;
static uint8_t width = 3;

void initPaint(void) {
    setFrame(0xffff);

    // color selection
    for (uint8_t i = 0; i < CTRL_COUNT; i++) {
       fillArea(CTRL_WIDTH * i, 0, CTRL_WIDTH, CTRL_WIDTH, colors[i]);
    }

    // tool selection
    fillArea(0, DISPLAY_WIDTH - CTRL_WIDTH - 1, 1, DISPLAY_HEIGHT, 0x0);
    for (uint8_t i = 0; i < 4; i++) {
        writeBitmap(CTRL_WIDTH * i + BITMAP_PADDING, DISPLAY_WIDTH - CTRL_WIDTH + BITMAP_PADDING, i);
        fillArea(CTRL_WIDTH * (i + 1), DISPLAY_WIDTH - CTRL_WIDTH, CTRL_WIDTH, 1, 0x0);
    }
}

void paintEvent(uint8_t event, Point *point) {
    if (point->x < CTRL_WIDTH) {
        if (event == EVENT_PRESS_DOWN) {
            // color selected
            // TODO highlight selected color
            uint8_t i = point->y / (CTRL_WIDTH + 1);
            color = colors[i];
        }
    } else if (point->x > DISPLAY_WIDTH - CTRL_WIDTH - 1 - width) {
        if (event == EVENT_PRESS_DOWN) {
            // TODO highlight selected tool
            uint8_t i = point->y / (CTRL_WIDTH + 1);
            if (i == TOOL_CLEAR) {
                fillArea(0, CTRL_WIDTH, DISPLAY_WIDTH - 2 * CTRL_WIDTH, DISPLAY_HEIGHT, 0xffff);
            } else {
                tool = i;
            }
            prev = (Point){-1};
        }
    } else {
        paintPoint(event, point);
    }
}

void paintPoint(uint8_t event, Point *point) {    
    if (tool == TOOL_ERASER) {
        fillArea(point->y, point->x, width, width, 0xffff);
    } else {
        // TODO center relative to thickness
        fillArea(point->y, point->x, width, width, color);
    }

    // connect points with a distance > 1 with a straight line
    if (prev.x != -1 && (
            (tool == TOOL_LINE) || 
            (tool == TOOL_FREEHAND && event == EVENT_CONTACT))) {
        float d = sqrt(pow(point->x - prev.x, 2) + pow(point->y - prev.y, 2));
        if (d > 1) {
            float xd = (point->x - prev.x) / d;
            float yd = (point->y - prev.y) / d;

            for (int i = 1; i < d; i++) {
                int xi = prev.x + xd * i;
                int yi = prev.y + yd * i;
                fillArea(yi, xi, width, width, color);
            }
        }
    }

    prev = *point;
}