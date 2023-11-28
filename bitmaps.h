/* 
 * File:   bitmaps.h
 * Author: torsten.roemer@luniks.net
 *
 * Created on 16. April 2023, 18:19
 */

#ifndef BITMAPS_H
#define BITMAPS_H

#include <stdint.h>
#include "types.h"

#define SMILE       0
#define BLUSH       1
#define GRIN        2
#define GRIN_TEAR   3
#define MELT        4
#define HUG         5
#define TONGUE      6
#define SMILE_TEAR  7
#define SAD         8
#define THUMB_UP    9
#define THUMB_DOWN  10
#define CAT_SMILE   11
#define CAT_ANGRY   12
#define SUN         13
#define MOON        14
#define HEART       15
#define BEERS       16
#define PIZZA       17
#define TREE        18
#define FLOWER      19
#define HERBS       20
#define CAR         21

/**
 * A bitmap with its width and height, and data.
 */
typedef struct {
    /** Width of the bitmap, must be a multiple of 8. */
    const width_t width;
    /** Height of the bitmap, must be a multiple of 8. */
    const height_t height;
    /** Color space of the bitmap. */
    const space_t space;
    /** The actual bitmap. */
    const __flash uint8_t *bitmap;
} Bitmap;

/**
 * Available bitmaps.
 */
extern const __flash Bitmap bitmaps[];

#endif /* BITMAPS_H */

