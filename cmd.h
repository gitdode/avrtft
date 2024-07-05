/* 
 * File:   cmd.h
 * Author: torsten.roemer@luniks.net
 *
 * Created on 18. April 2023, 21:18
 */

#ifndef CMD_H
#define CMD_H

#include <string.h>
#include <stdlib.h>
#include "usart.h"
#include "tft.h"
#include "display.h"
#include "font.h"
#include "hack.h"
#include "bitmaps.h"
#include "bmp.h"
#include "sdcard.h"
#include "paint.h"

/** Clear frame buffer: 'c <0x0000 - 0xffff>'. */
#define CMD_CLEAR       'c'

/** Display one line of text: 't <X> <Y> <font> <text>'. */
#define CMD_TEXT        't'

/** Display a bitmap: 'b <X> <Y> <index>'. */
#define CMD_BITMAP      'b'

/** Prepare "streaming" a .bmp: 'p <X> <Y>'. */
#define CMD_BMP         'p'

/** Read a .bmp: from SD card: 's <address>'. */
#define CMD_BMP_SD      's'

/** Display Hack demo: 'd'. */
#define CMD_DEMO        'd'

/** Paint toy: 'a'. */
#define CMD_PAINT       'a'

/**
 * Handles the given command.
 * @param data
 */
void handleCmd(char *data);

#endif /* CMD_H */
