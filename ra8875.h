/* 
 * File:   ra8875.h
 * Author: torsten.roemer@luniks.net
 *
 * Created on 1. Juni 2024, 15:32
 */

#ifndef RA8875_H
#define RA8875_H

#include <util/delay.h>
#include "tft.h"
#include "touch.h"
#include "types.h"
#include "pins.h"
#include "usart.h"
#include "spi.h"

#define CMD_WRITE   0x80
#define STATUS_READ 0xc0
#define DATA_WRITE  0x00
#define DATA_READ   0x40

/* System & Configuration Registers */
#define PWRR    0x01
#define MRWC    0x02
#define PCSR    0x04
#define SYSR    0x10

/* Horizontal (Sync) Registers */
#define HDWR    0x14
#define HNDFTR  0x15
#define HNDR    0x16
#define HSTR    0x17
#define HPWR    0x18

/* Vertical (Sync) Registers */
#define VDHR0   0x19
#define VDHR1   0x1a
#define VNDR0   0x1b
#define VNDR1   0x1c
#define VSTR0   0x1d
#define VSTR1   0x1e
#define VPWR    0x1f

/* LCD Display Control Registers */
#define DPCR    0x20
#define FNCR0   0x21
#define FNCR1   0x22
#define F_CURXL 0x2a
#define F_CURXH 0x2b
#define F_CURYL 0x2c
#define F_CURYH 0x2d

/* Active Window & Scroll Window Setting Registers */
#define HSAW0   0x30
#define HSAW1   0x31
#define VSAW0   0x32
#define VSAW1   0x33
#define HEAW0   0x34
#define HEAW1   0x35
#define VEAW0   0x36
#define VEAW1   0x37

/* Cursor Setting Registers */
#define MWCR0   0x40
#define CURH0   0x46
#define CURH1   0x47
#define CURV0   0x48
#define CURV1   0x49

/* Background Color Registers */
#define BGCR0   0x60
#define BGCR1   0x61
#define BGCR2   0x62

/* Foreground Color Registers */
#define FGCR0   0x63
#define FGCR1   0x64
#define FGCR2   0x65

/* Touch Panel Control Registers */
#define TPCR0   0x70
#define TPCR1   0x71
#define TPXH    0x72
#define TPYH    0x73
#define TPXYL   0x74

/* Interrupt Control Registers */
#define INTC1   0xf0
#define INTC2   0xf1

/* PLL Setting Registers */
#define PLLC1   0x88
#define PLLC2   0x89

/*  PWM Control Registers */
#define P1CR    0x8a
#define P1DCR   0x8b

/* Memory Clear Control Register */
#define MCLR    0x8e

/* Drawing Contol Registers */
#define DCR     0x90
#define DCHR0   0x99
#define DCHR1   0x9a
#define DCVR0   0x9b
#define DCVR1   0x9c
#define DCRR    0x9d

/*  Key & IO Control Registers */
#define GPIOX   0xc7

/* HSync + VSync currently only for 800x480 */
#define HNDFT   0
#define HNDP    10 
#define HSP     32
#define HPW     96

#define VNDP    32
#define VSP     23
#define VPW     2

/**
 * Writes given text at given coordinates and foreground and background color.
 * 
 * @param x
 * @param y
 * @param fg
 * @param bg
 * @param string
 */
void writeText(x_t x, y_t y, uint16_t fg, uint16_t bg, char *string);

#endif /* RA8875_H */
