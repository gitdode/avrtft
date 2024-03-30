/* 
 * File:   types.h
 * Author: torsten.roemer@luniks.net
 *
 * Created on 17. September 2023, 20:33
 */

#ifndef TYPES_H
#define TYPES_H

#include <stdbool.h>

/* Width, height and color space of bitmaps and glyphs */
typedef uint16_t    width_t;
typedef uint16_t    height_t;
typedef uint8_t     space_t;

/* Width * height * bytes per pixel */
typedef uint32_t    bytes_t;

/* Number of rows and columns of the display */
typedef uint16_t    row_t;
typedef uint16_t    col_t;

/* Char code (like UTF-8 code point) */
typedef uint8_t     code_t;

/* Number of glyphs of a font */
typedef uint8_t     length_t;

/**
 * A point with its x and y coordinates.
 */
typedef struct {
    int16_t x;
    int16_t y;
} Point;

/**
 * Pointer to a function that takes an array of bytes
 * and returns a boolean.
 */
typedef bool (*consumer)(uint8_t*);

#endif /* TYPES_H */

