/* 
 * File:   draw.c
 * Author: torsten.roemer@luniks.net
 *
 * Created on 29. Dezember 2023, 18:01
 */

#include "draw.h"

static Point prev = {0};

void draw(uint8_t event, Point *point, uint16_t color, uint8_t thickness) {
    // TODO hflip, vflip
    // writeBitmap(DISPLAY_HEIGHT - point->x, point->y, 1);
    // TODO center relative to thickness
    fillArea(DISPLAY_HEIGHT - point->x, point->y, thickness, thickness, color);

    // TODO optimize
    if (event == T_EVT_CONTACT) {
        float d = sqrt(pow(point->x - prev.x, 2) + pow(point->y - prev.y, 2));
        if (d > 1) {
            float xd = (point->x - prev.x) / d;
            float yd = (point->y - prev.y) / d;

            for (int i = 1; i < d; i++) {
                int xi = prev.x + xd * i;
                int yi = prev.y + yd * i;
                fillArea(DISPLAY_HEIGHT - xi, yi, thickness, thickness, color);
            }
        }
    }

    prev = *point;
}