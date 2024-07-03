/* 
 * File:   colorspace.h
 * Author: torsten.roemer@luniks.net
 *
 * Created on 3. Juli 2024, 19:02
 */

#ifndef COLORSPACE_H
#define COLORSPACE_H

// TODO use enum? typedef?
#define SPACE_MONO1  1
#define SPACE_GREY4  4
#define SPACE_RGB16  16

#include <stdint.h>

/**
 * Converts the given 8 pixel in 1-Bit monochrome to 16-Bit RGB (5/6/5) color
 * stored in the given array of 16 bytes.
 * 
 * @param grey 8 pixel in 1-Bit monochrome
 * @param rgb 8 pixel in 16-Bit RGB (5/6/5) color
 */
void mono1ToRGB16(uint8_t mono, uint8_t *rgb);

/*
 * Converts the given two pixel in 4-Bit greyscale to 16-Bit RGB (5/6/5) color
 * stored in the given array of four bytes.
 * 
 * @param grey two pixel in 4-Bit greyscale
 * @param rgb two pixel in 16-Bit RGB (5/6/5) color
 */
void grey4ToRGB16(uint8_t grey, uint8_t *rgb);

#endif /* COLORSPACE_H */

