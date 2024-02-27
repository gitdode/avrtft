/* 
 * File:   sdcard.h
 * Author: torsten.roemer@luniks.net
 *
 * Created on 24. Februar 2024, 00:13
 */

#ifndef SDCARD_H
#define SDCARD_H

#include <stdbool.h>
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

#define CMD17       17
#define CMD17_CRC   0x00

#define CMD55       55
#define CMD55_ARG   0x00000000
#define CMD55_CRC   0x00

#define CMD58       58
#define CMD58_ARG   0x00000000
#define CMD58_CRC   0x00

#define ACMD41      41
#define ACMD41_ARG  0x40000000
#define ACMD41_CRC  0x00

#define CMD_ILLEGAL     2
#define SD_MAX_READ     50000 // SPI clock ticks in 100 ms
#define SD_BLOCK_SIZE   512

/**
 * Initializes the SD Card and returns true on success, false otherwise.
 * 
 * @return true on success, false otherwise
 */
bool initSDCard(void);

void readSDCard(void);

#endif /* SDCARD_H */
