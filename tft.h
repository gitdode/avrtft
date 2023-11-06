/* 
 * File:   tft.h
 * Author: torsten.roemer@luniks.net
 *
 * Created on 6. November 2023, 18:45
 */

#ifndef TFT_H
#define TFT_H

#include <stdbool.h>

#define SOME_DISPLAY_COMMAND       0x01

#define DISPLAY_WIDTH   160
#define DISPLAY_HEIGHT  128

/**
 * Sets display to send a command.
 */
void displaySetCmd(void);

/**
 * Sets display to send data.
 */
void displaySetData(void);

/**
 * Sends the given command to the display.
 */
void displayCmd(uint8_t cmd);

/**
 * Sends the given data to the display.
 */
void displayData(uint8_t data);

/**
 * Initializes the display.
 */
void initDisplay(void);

/**
 * Updates the display.
 */
void updateDisplay(void);

#endif /* TFT_H */
