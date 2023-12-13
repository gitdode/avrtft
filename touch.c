/* 
 * File:   touch.c
 * Author: torsten.roemer@luniks.net
 *
 * Created on 12. Dezember 2023, 23:44
 */

#include <avr/interrupt.h>
#include "touch.h"
#include "usart.h"

ISR(INT0_vect) {
    printString("touch!\r\n");
}