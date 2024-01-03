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

static uint8_t tool = TOOL_FREE;
static Point prev = {0};
static uint16_t color = 0x0;
static uint8_t thick = 3; // line thickness
static uint8_t thoff = 2; // offset to "center" point relative to thickness

/**
 * Paints the color selection.
 */
static void paintColors(void) {
    for (uint8_t i = 0; i < CTRL_COUNT; i++) {
       fillArea(CTRL_WIDTH * i, 0, CTRL_WIDTH, CTRL_WIDTH, colors[i]);
    }    
}

/**
 * Paints the tool selection.
 */
static void paintTools(void) {
    fillArea(0, DISPLAY_WIDTH - CTRL_WIDTH, 
             CTRL_WIDTH, CTRL_WIDTH * TOOL_COUNT, 0xffff);
    for (uint8_t i = 0; i < TOOL_COUNT; i++) {
        drawRectangle(CTRL_WIDTH * i, DISPLAY_WIDTH - CTRL_WIDTH, 
                      CTRL_WIDTH, CTRL_WIDTH + 1, 1, 0x0);
        writeBitmap(CTRL_WIDTH * i + BITMAP_PADDING, 
                    DISPLAY_WIDTH - CTRL_WIDTH + BITMAP_PADDING, i);
    }
}

void initPaint() {
    setFrame(0xffff);

    // color selection
    paintColors();

    // tool selection
    paintTools();
    
    // highlight default tool
    drawRectangle(CTRL_WIDTH * tool, DISPLAY_WIDTH - CTRL_WIDTH, 
                  CTRL_WIDTH, CTRL_WIDTH + 1, 2, 0x0);
}

void paintEvent(uint8_t event, Point *point) {
    if (point->x < CTRL_WIDTH + thoff) {
        if (event == EVENT_PRESS_DOWN) {
            // color selected
            uint8_t i = point->y / (CTRL_WIDTH + 1);
            paintColors();
            drawRectangle(CTRL_WIDTH * i, 0, 
                          CTRL_WIDTH, CTRL_WIDTH, 2, 0x0);
            color = colors[i];
        }
    } else if (point->x > DISPLAY_WIDTH - CTRL_WIDTH - thoff) {
        if (event == EVENT_PRESS_DOWN) {
            uint8_t i = point->y / (CTRL_WIDTH + 1);
            if (i == TOOL_CLEAR) {
                // clear canvas
                fillArea(0, CTRL_WIDTH, DISPLAY_WIDTH - 2 * CTRL_WIDTH + 1, 
                         DISPLAY_HEIGHT, 0xffff);
            } else if (i == TOOL_THICK) {
                // increment line thickness
                thick += 3;
                if (thick > 12) thick = 3;
                thoff = thick / 2 + 1;
            } else if (i < TOOL_COUNT) {
                // repaint tools, highlight and select tool
                paintTools();
                drawRectangle(CTRL_WIDTH * i, DISPLAY_WIDTH - CTRL_WIDTH, 
                              CTRL_WIDTH, CTRL_WIDTH + 1, 2, 0x0);
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
        fillArea(point->y - thoff, point->x - thoff, thick, thick, 0xffff);
    } else {
        fillArea(point->y - thoff, point->x - thoff, thick, thick, color);
    }

    if (prev.x != -1) {
        // connect previous and current point with a straight line if distance > 1
        if ((tool == TOOL_LINE) || 
            (tool == TOOL_FREE && event == EVENT_CONTACT)) {
            float d = sqrt(pow(point->x - prev.x, 2) + pow(point->y - prev.y, 2));
            if (d > 1) {
                float xd = (point->x - prev.x) / d;
                float yd = (point->y - prev.y) / d;

                for (int i = 1; i < d; i++) {
                    col_t xi = prev.x + xd * i;
                    row_t yi = prev.y + yd * i;
                    fillArea(yi - thoff, xi - thoff, thick, thick, color);
                }
            }
        }
        
        // draw a rectangle spanning the previous and current point
        if (tool == TOOL_RECT && event == EVENT_PRESS_DOWN) {
            row_t x1 = fmin(prev.x, point->x);
            row_t y1 = fmin(prev.y, point->y);
            col_t x2 = fmax(prev.x, point->x);
            col_t y2 = fmax(prev.y, point->y);
            
            drawRectangle(y1 - thoff, x1 - thoff, 
                          x2 - x1 + thick, y2 - y1 + thick, thick, color);
            // unset previous point and leave (for now)
            prev = (Point){-1};
            return;
        }
    }

    prev = *point;
}