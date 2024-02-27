/* 
 * File:   sdcard.c
 * Author: torsten.roemer@luniks.net
 * 
 * Thanks to http://rjhcoding.com/avrc-sd-interface-1.php ff.
 *
 * Created on 24. Februar 2024, 00:13
 */

#include "sdcard.h"
#include "bmp.h"

/**
 * Transmits the given command, argument and CRC value.
 * 
 * @param command
 * @param argument
 * @param crc
 */
static void command(uint8_t command, uint32_t argument, uint8_t crc) {
    // 6-bit command, start bit is always 0, transmitter bit is 1 (host command)
    transmit(command | 0x40);

    transmit(argument >> 24);
    transmit(argument >> 16);
    transmit(argument >> 8);
    transmit(argument);

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

/**
 * Sends CMD17 to read a single block at the given address, 
 * reads the block into the given array and returns the R1 response.
 * 
 * @param address
 * @param block
 * @return R1
 */
static uint8_t readSingleBlock(uint32_t address, uint8_t *block) {
    select();
    
    command(CMD17, address, CMD17_CRC);
    uint8_t response = readR1();

    if (response == 0x00) {
        // read command was successful, wait for start block token
        uint8_t token = 0xff;
        for (uint16_t attempt = 0; attempt < SD_MAX_READ && token == 0xff; attempt++) {
            token = transmit(0xff);
        }

        if (token == 0xfe) {
            // start block token received, 512 data bytes follow
            for (uint16_t i = 0; i < SD_BLOCK_SIZE; i++) {
                block[i] = transmit(0xff);
            }
            
            // 16-bit CRC (ignore for now)
            transmit(0xff);
            transmit(0xff);
        }
    }
    
    deselect();
    
    return response;
}

bool initSDCard(void) {
    uint8_t response[5];
    
    // power on
    powerOn();

    // go to idle state
    response[0] = sendIdle();
    if (response[0] > 0x01) {
        printString("sd card error\r\n");
        printByte(response[0]);
        return false;
    }

    // send interface condition
    sendIfCond(response);
    if (response[0] & (1 << CMD_ILLEGAL)) {
        printString("sd card is V1.x or not sd card\r\n");
        return false;
    } else if (response[0] > 0x01) {
        printString("sd card error\r\n");
        return false;
    } else if (response[4] != 0xaa) {
        printString("sd card echo pattern mismatch\r\n");
        return false;
    }
    
    uint8_t attempts = 0;
    do {
        if (attempts > 100) {
            printString("sd card did not become ready\r\n");
            return false;
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
        return false;
    } else if (!(response[1] & 0x80)) {
        printString("sd card not ready\r\n");
        return false;
    }

    printString("sd card ready\r\n");
    
    return true;
}

void readSDCard(void) {
    uint8_t block[SD_BLOCK_SIZE];
    uint8_t response = readSingleBlock(0, block);
    if (response == 0x00) {
        for (uint16_t i = 0; i < SD_BLOCK_SIZE; i++) {
            char buf[3];
            snprintf(buf, sizeof (buf), "%02x", block[i]);
            printString(buf);
        }
        printString("\r\n");
    }
}
