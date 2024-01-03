/* 
 * File:   cmd.h
 * Author: torsten.roemer@luniks.net
 *
 * Created on 18. April 2023, 21:18
 */

#ifndef CMD_H
#define CMD_H

/** Clear frame buffer: 'c <0x0000 - 0xffff>'. */
#define CMD_CLEAR       'c'

/** Display one line of text: 't <row> <col> <font> <text>'. */
#define CMD_TEXT        't'

/** Display a bitmap: 'b <row> <col> <index>'. */
#define CMD_BITMAP      'b'

/** Prepare "streaming" a .bmp: 'p <row> <col>'. */
#define CMD_BMP         'p'

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
