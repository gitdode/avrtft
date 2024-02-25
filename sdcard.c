/* 
 * File:   sdcard.c
 * Author: torsten.roemer@luniks.net
 * 
 * Thanks to http://rjhcoding.com/avrc-sd-interface-1.php
 *
 * Created on 24. Februar 2024, 00:13
 */

#include "sdcard.h"

/**
 * Transmits the given command, argument and CRC value.
 * 
 * @param cmd
 * @param arg
 * @param crc
 */
static void command(uint8_t cmd, uint32_t arg, uint8_t crc) {
    // 6-bit command, start bit is always 0, transmitter bit is 1 (host command)
    transmit(cmd | 0x40);

    transmit(arg >> 24);
    transmit(arg >> 16);
    transmit(arg >> 8);
    transmit(arg);

    // 7-bit crc, end bit is always 1
    transmit(crc | 0x01);
}

/**
 * Reads an R1 response and returns it.
 * 
 * @return R1
 */
static uint8_t readR1(void) {
    uint8_t i = 0; 
    uint8_t response;

    // poll up to 8 times for response    
    while ((response = transmit(0xff)) == 0xff) {
        i++;
        if (i > 8) { 
            break;
        }
    }

    return response;
}

/**
 * Reads an R3/R7 response into the given array of 5 bytes.
 * 
 * @param R3/R7
 */
static void readR3_7(uint8_t *response) {
    // read R1
    response[0] = readR1();

    // stop reading if R1 has an error
    if (response[0] > 0b00000001) {       
        return;
    }

    response[1] = transmit(0xff);
    response[2] = transmit(0xff);
    response[3] = transmit(0xff);
    response[4] = transmit(0xff);
}

/**
 * SPI selects the sd card with extra clocks before and after.
 */
static void select(void) {
    transmit(0xff);
    sdCardSel();
    transmit(0xff);
}

/**
 * SPI deselects the sd card with extra clocks before and after.
 */
static void deselect(void) {
    transmit(0xff);
    sdCardDes();
    transmit(0xff);
}

/**
 * Runs the power on sequence.
 */
static void powerOn(void) {
    deselect();

    // supply ramp up time
    _delay_ms(1);

    // supply at least 74 clocks
    for (uint8_t i = 0; i < 10; i++) {
        transmit(0xff);
    }

    deselect();
}

/**
 * Sends CMD0 to set idle SPI mode and returns the R1 response.
 * 
 * @return R1.
 */
static uint8_t sendIdle(void) {
    select();

    command(CMD0, CMD0_ARG, CMD0_CRC);
    uint8_t response = readR1();

    deselect();

    return response;
}

/**
 * Sends CMD8 to check version and voltage and reads the R7 response
 * into the given array of 5 bytes.
 * 
 * @param R7
 */
static void sendIfCond(uint8_t *response) {
    select();

    command(CMD8, CMD8_ARG, CMD8_CRC);
    readR3_7(response);

    deselect();
}

/**
 * Sends CMD58 to check version and voltage and reads the R3 response
 * into the given array of 5 bytes.
 * 
 * @param R3
 */
static void sendOCR(uint8_t *response) {
    select();

    command(CMD58, CMD58_ARG, CMD58_CRC);
    readR3_7(response);

    deselect();
}

void initSDCard(void) {
    // power on
    powerOn();

    // go to idle state
    uint8_t idle = sendIdle();
    if (idle > 0b00000001) {
        printString("sd card error\r\n");
        printByte(idle);
        return;
    }

    // send interface condition
    uint8_t ifcond[5];
    sendIfCond(ifcond);
    if (ifcond[0] & (1 << CMD_ILLEGAL)) {
        printString("sd card is V1.x or not sd card\r\n");
        return;
    } else if (ifcond[0] > 0b00000001) {
        printString("sd card error\r\n");
        return;
    } else if (ifcond[4] != 0xaa) {
        printString("sd card echo pattern mismatch\r\n");
        return;
    }
    
    // send operation conditions register 
    uint8_t ocr[5];
    sendOCR(ocr);
    if (ocr[0] > 0b00000001) {
        printString("sd card error\r\n");
        return;
    }

    /*
    printByte(ocr[0]);
    printByte(ocr[1]);
    printByte(ocr[2]);
    printByte(ocr[3]);
    printByte(ocr[4]);
    */
    
    printString("sd card looks good so far\r\n");
}

void readSDCard(void) {
    
}
