/* 
 * File:   bmp.h
 * Author: dode
 *
 * Created on 22. November 2023, 23:10
 */

#ifndef BMP_H
#define BMP_H

#include <stdint.h>
#include <stdbool.h>
#include "types.h"

void prepare(row_t row, col_t col);

void stream(uint8_t byte);

#endif /* BMP_H */

