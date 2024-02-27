/* 
 * File:   sdcard.c
 * Author: torsten.roemer@luniks.net
 * 
 * Thanks to http://rjhcoding.com/avrc-sd-interface-1.php ff.
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

    // stop reading if R1 indicates an error
    if (response[0] > 0x01) {
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
 * @return R1
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

/**
 * Sends CMD55 to tell that an app command is next and returns the R1 response.
 * 
 * @return R1
 */
static uint8_t sendApp(void) {
    select();

    command(CMD55, CMD55_ARG, CMD55_CRC);
    uint8_t response = readR1();

    deselect();

    return response;
}

/**
 * Sends ACMD41 to start initialization and returns the R1 response.
 * 
 * @return R1
 */
static uint8_t sendOpCond(void) {
    select();

    command(ACMD41, ACMD41_ARG, ACMD41_CRC);
    uint8_t response = readR1();

    deselect();

    return response;
}

void initSDCard(void) {
    uint8_t response[5];
    
    // power on
    powerOn();

    // go to idle state
    response[0] = sendIdle();
    if (response[0] > 0x01) {
        printString("sd card error\r\n");
        printByte(response[0]);
        return;
    }

    // send interface condition
    sendIfCond(response);
    if (response[0] & (1 << CMD_ILLEGAL)) {
        printString("sd card is V1.x or not sd card\r\n");
        return;
    } else if (response[0] > 0x01) {
        printString("sd card error\r\n");
        return;
    } else if (response[4] != 0xaa) {
        printString("sd card echo pattern mismatch\r\n");
        return;
    }
    
    uint8_t attempts = 0;
    do {
        if (attempts > 100) {
            printString("sd card did not become ready\r\n");
            return;
        }
        
        // send app command
        response[0] = sendApp();
        if (response[0] < 0x02) {
            // start initialization
            response[0] = sendOpCond();
        }
        
        _delay_ms(10);
        attempts++;
    } while (response[0] != 0x00);
   
    // send operation conditions register 
    sendOCR(response);
    if (response[0] > 0x01) {
        printString("sd card error\r\n");
        return;
    } else if (!(response[1] & 0x80)) {
        printString("sd card not ready\r\n");
        return;
    }

    /*
    printByte(response[0]);
    printByte(response[1]);
    printByte(response[2]);
    printByte(response[3]);
    printByte(response[4]);
    */
    
    printString("sd card looks good so far\r\n");
}

void readSDCard(void) {
    
}
