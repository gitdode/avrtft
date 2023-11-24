/* 
 * File:   pins.h
 * Author: torsten.roemer@luniks.net
 *
 * Created on 1. April 2023, 19:25
 */

#ifndef PINS_H
#define PINS_H

#include <avr/io.h>

/* SPI */
#define DDR_SPI   DDRB
#define PORT_SPI  PORTB
#define PIN_SS    PB2
#define PIN_MOSI  PB3
#define PIN_MISO  PB4
#define PIN_SCK   PB5

/* Display SPI */
#define DDR_DSPI  DDRB
#define PORT_DSPI PORTB
#define PIN_DCS   PB1 // display chip select
#define PIN_DC    PB0 // display data/command

/* Display other */
#define DDR_DISP  DDRD
#define PORT_DISP PORTD
#define PIN_RST   PD7 // display reset

#endif /* PINS_H */
