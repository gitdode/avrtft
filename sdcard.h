/* 
 * File:   sdcard.h
 * Author: torsten.roemer@luniks.net
 *
 * Created on 24. Februar 2024, 00:13
 */

#ifndef SDCARD_H
#define SDCARD_H

#include <util/delay.h>
#include "pins.h"
#include "spi.h"
#include "usart.h"

#define CMD0        0
#define CMD0_ARG    0x00000000
#define CMD0_CRC    0x94

#define CMD8        8
#define CMD8_ARG    0x0000001aa
#define CMD8_CRC    0x86

#define CMD58       58
#define CMD58_ARG   0x00000000
#define CMD58_CRC   0x00

#define CMD_ILLEGAL 2

/**
 * Initializes the SD Card.
 */
void initSDCard(void);

void readSDCard(void);

#endif /* SDCARD_H */
