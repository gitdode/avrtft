/* 
 * File:   i2c.h
 * Author: torsten.roemer@luniks.net
 *
 * Created on 15. Dezember 2023, 19:01
 */

#ifndef I2C_H
#define I2C_H

#include <avr/io.h>
#include "pins.h"

void i2cStart(void);

void i2cStop(void);

void i2cSend(uint8_t data);

uint8_t i2cReadAck(void);

uint8_t i2cRead(void);

#endif /* I2C_H */

