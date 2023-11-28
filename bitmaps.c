/*
 * File:   bitmaps.c
 * Author: torsten.roemer@luniks.net
 *
 * Created on 6. November 2023, 18:45
 */

#include <stdio.h>
#include "bitmaps.h"
#include "tft.h"
#include "utils.h"

const __flash uint8_t LINUS_GREY4_DATA[] = {
    0xff, 0xfe, 0xee, 0xcd, 0xed, 0xdc, 0xcc, 0xbb, 0xbc, 0xef, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xfe, 0xee, 0xcd, 0xed, 0xdc, 0xcc, 0xbb, 0xbc, 0xd6, 0x6f, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xfe, 0xee, 0xcd, 0xed, 0xdc, 0xcc, 0xbb, 0xbc, 0x81, 0x1b, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xfe, 0xee, 0x96, 0xcd, 0xdc, 0xcc, 0xbb, 0xbb, 0x31, 0x16, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xfe, 0xee, 0xa2, 0x4a, 0xdc, 0xcc, 0xbb, 0xb9, 0x11, 0x11, 0xef, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xfe, 0xee, 0xc3, 0x34, 0x8c, 0xcb, 0xbb, 0xa4, 0x11, 0x21, 0xcf, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xee, 0xde, 0xc7, 0x24, 0x34, 0x68, 0x97, 0x40, 0x11, 0x11, 0xaf, 0xff, 0xff, 0xff, 0xff,
    0xfe, 0xdd, 0xce, 0xca, 0x24, 0x31, 0x13, 0x33, 0x10, 0x10, 0x00, 0x5e, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xed, 0xcd, 0xcb, 0x71, 0x40, 0x11, 0x13, 0x11, 0x10, 0x00, 0x2b, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xfe, 0xdd, 0xcc, 0x93, 0x31, 0x01, 0x13, 0x00, 0x11, 0x00, 0x19, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xfe, 0xdd, 0xcb, 0xa4, 0x41, 0x01, 0x12, 0x00, 0x11, 0x00, 0x14, 0xef, 0xff, 0xff, 0xff,
    0xff, 0xee, 0xdd, 0xdb, 0xa3, 0x20, 0x00, 0x00, 0x21, 0x01, 0x10, 0x12, 0xbf, 0xff, 0xff, 0xff,
    0xee, 0xed, 0xcd, 0xdb, 0x61, 0x30, 0x00, 0x04, 0x65, 0x00, 0x00, 0x11, 0x8f, 0xff, 0xff, 0xff,
    0xef, 0xee, 0xcd, 0xda, 0x22, 0x64, 0x10, 0x03, 0x51, 0x00, 0x00, 0x01, 0x4d, 0xff, 0xff, 0xff,
    0xee, 0xed, 0xcc, 0xda, 0x21, 0x32, 0x11, 0x00, 0x00, 0x00, 0x01, 0x01, 0x38, 0xff, 0xff, 0xff,
    0xef, 0xed, 0xcc, 0xd9, 0x21, 0x01, 0x41, 0x00, 0x00, 0x00, 0x00, 0x12, 0x44, 0xbf, 0xff, 0xff,
    0xee, 0xed, 0xcc, 0xca, 0x31, 0x13, 0x31, 0x00, 0x01, 0x22, 0x22, 0x10, 0x33, 0x7e, 0xff, 0xff,
    0xef, 0xed, 0xcc, 0xcb, 0x51, 0x21, 0x10, 0x00, 0x12, 0x43, 0x23, 0x32, 0x22, 0x5d, 0xff, 0xff,
    0xee, 0xed, 0xcc, 0xcb, 0x94, 0x42, 0x14, 0x10, 0x14, 0x54, 0x33, 0x34, 0x33, 0x4a, 0xef, 0xff,
    0xff, 0xed, 0xcb, 0xcb, 0xb8, 0x64, 0x41, 0x01, 0x23, 0x43, 0x44, 0x44, 0x42, 0x38, 0xee, 0xff,
    0xff, 0xfd, 0xcb, 0xcb, 0xb8, 0x55, 0x65, 0x11, 0x13, 0x56, 0x78, 0x95, 0x32, 0x37, 0xde, 0xee,
    0xff, 0xed, 0xcb, 0xcb, 0xb7, 0x58, 0x66, 0x65, 0x67, 0x89, 0x9a, 0x83, 0x43, 0x26, 0xde, 0xee,
    0xee, 0xcc, 0xcb, 0xbb, 0xb6, 0x58, 0x98, 0x88, 0x88, 0x99, 0xaa, 0x71, 0x13, 0x36, 0xce, 0xed,
    0xdc, 0xcc, 0xbb, 0xbb, 0xb8, 0x99, 0x99, 0x98, 0x99, 0x99, 0x99, 0x72, 0x21, 0x25, 0x8c, 0xdd,
    0xcc, 0xcc, 0xbb, 0xbb, 0xb8, 0x79, 0x99, 0x99, 0x99, 0x99, 0xa8, 0x51, 0x11, 0x35, 0x47, 0xcc,
    0xcc, 0xbb, 0xba, 0xbb, 0xa9, 0x57, 0x88, 0x99, 0x99, 0x99, 0x73, 0x01, 0x01, 0x35, 0x33, 0x8c
};

const __flash uint8_t LINUS_RGB16_DATA[] = {
    0xff, 0xff, 0xff, 0xfd, 0xff, 0xdd, 0xf7, 0x7b, 0xef, 0x5a, 0xef, 0x18, 0xde, 0x76, 0xe6, 0xf7,
    0xef, 0x18, 0xee, 0xf7, 0xee, 0xd7, 0xe6, 0x75, 0xde, 0x34, 0xd6, 0x14, 0xd5, 0xf3, 0xcd, 0xb2,
    0xcd, 0xd3, 0xe6, 0x75, 0xf7, 0x38, 0xff, 0x9a, 0xff, 0xbb, 0xff, 0xfd, 0xff, 0xfe, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe,
    0xff, 0xff, 0xff, 0xfd, 0xff, 0xdc, 0xef, 0x7a, 0xef, 0x59, 0xef, 0x39, 0xde, 0x76, 0xe6, 0xd7,
    0xef, 0x17, 0xee, 0xf7, 0xee, 0xd7, 0xe6, 0x75, 0xde, 0x34, 0xd6, 0x14, 0xd5, 0xf3, 0xcd, 0xb2,
    0xcd, 0xd3, 0xde, 0x55, 0xe6, 0xb6, 0x73, 0x4b, 0x73, 0x6b, 0xf7, 0xbc, 0xff, 0xfe, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe,
    0xff, 0xff, 0xff, 0xfd, 0xff, 0xdc, 0xf7, 0x7a, 0xef, 0x39, 0xef, 0x38, 0xd6, 0x55, 0xe6, 0xb7,
    0xef, 0x18, 0xee, 0xf7, 0xee, 0xd7, 0xe6, 0x75, 0xde, 0x34, 0xd6, 0x14, 0xd5, 0xf3, 0xcd, 0xb2,
    0xcd, 0xb3, 0xde, 0x34, 0x9c, 0x6f, 0x30, 0xe2, 0x39, 0x02, 0xc5, 0xf5, 0xff, 0xfe, 0xff, 0xfe,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe,
    0xff, 0xff, 0xff, 0xfd, 0xf7, 0xbc, 0xf7, 0x7a, 0xef, 0x39, 0xef, 0x38, 0xac, 0xf1, 0x7b, 0x8c,
    0xd6, 0x55, 0xee, 0xf7, 0xe6, 0xd7, 0xe6, 0x75, 0xde, 0x34, 0xd6, 0x14, 0xd5, 0xd3, 0xcd, 0xb2,
    0xc5, 0xb2, 0xcd, 0xd3, 0x4a, 0x07, 0x28, 0xe3, 0x31, 0x03, 0x73, 0x2b, 0xff, 0xdd, 0xff, 0xfe,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe,
    0xff, 0xff, 0xff, 0xdd, 0xf7, 0xbc, 0xf7, 0x7a, 0xef, 0x39, 0xef, 0x39, 0xb5, 0x31, 0x41, 0x44,
    0x5a, 0x89, 0xb5, 0x73, 0xe6, 0xb6, 0xe6, 0x75, 0xde, 0x34, 0xd6, 0x14, 0xd5, 0xf3, 0xcd, 0xb2,
    0xc5, 0x92, 0xa4, 0xaf, 0x31, 0x44, 0x29, 0x04, 0x29, 0x03, 0x31, 0x03, 0xe7, 0x1a, 0xff, 0xfe,
    0xff, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xf7, 0xdc, 0xf7, 0x9b, 0xf7, 0x7a, 0xef, 0x39, 0xef, 0x18, 0xd6, 0x35, 0x51, 0xc5,
    0x49, 0xc5, 0x5a, 0xaa, 0x94, 0x70, 0xd6, 0x15, 0xde, 0x14, 0xd5, 0xf3, 0xd5, 0xf3, 0xcd, 0xb2,
    0xbd, 0x72, 0x5a, 0x88, 0x29, 0x24, 0x31, 0x24, 0x39, 0x44, 0x31, 0x23, 0xd6, 0x77, 0xff, 0xfd,
    0xff, 0xfe, 0xff, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe,
    0xff, 0xdd, 0xf7, 0x9b, 0xef, 0x7a, 0xef, 0x59, 0xe7, 0x18, 0xef, 0x18, 0xde, 0x76, 0x8b, 0xcd,
    0x49, 0x43, 0x62, 0xaa, 0x41, 0xe7, 0x52, 0xaa, 0x7b, 0x8d, 0x94, 0x91, 0xa4, 0xf2, 0x84, 0x0f,
    0x5a, 0xaa, 0x18, 0xc2, 0x28, 0xe3, 0x28, 0xe3, 0x31, 0x03, 0x31, 0x03, 0xad, 0x32, 0xff, 0xfd,
    0xff, 0xfe, 0xff, 0xfe, 0xff, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe,
    0xf7, 0xbc, 0xe7, 0x5a, 0xe7, 0x19, 0xde, 0xb7, 0xde, 0x96, 0xef, 0x18, 0xde, 0x76, 0xbd, 0x92,
    0x49, 0xa5, 0x5a, 0x48, 0x4a, 0x07, 0x20, 0xe4, 0x29, 0x24, 0x39, 0xe8, 0x39, 0xe7, 0x39, 0xe7,
    0x21, 0x24, 0x18, 0xc3, 0x20, 0xe3, 0x20, 0xc2, 0x18, 0xa2, 0x20, 0xc3, 0x62, 0xea, 0xf7, 0x7b,
    0xff, 0xfd, 0xff, 0xfe, 0xff, 0xfe, 0xff, 0xfe, 0xff, 0xfe, 0xff, 0xfe, 0xff, 0xfe, 0xff, 0xfe,
    0xff, 0xfe, 0xf7, 0xbc, 0xef, 0x9b, 0xe6, 0xf9, 0xde, 0x76, 0xe6, 0xf8, 0xde, 0x76, 0xd5, 0xf4,
    0x8b, 0xcc, 0x31, 0x24, 0x52, 0x89, 0x18, 0xc3, 0x20, 0xe3, 0x21, 0x04, 0x21, 0x04, 0x39, 0xe7,
    0x21, 0x04, 0x21, 0x04, 0x21, 0x04, 0x20, 0xc3, 0x10, 0x82, 0x10, 0x82, 0x31, 0x65, 0xc5, 0xd5,
    0xff, 0xfd, 0xff, 0xfd, 0xff, 0xfe, 0xff, 0xfe, 0xff, 0xfe, 0xff, 0xfe, 0xff, 0xfe, 0xff, 0xfe,
    0xf7, 0xbc, 0xf7, 0xbb, 0xf7, 0xbb, 0xe7, 0x39, 0xde, 0x97, 0xe6, 0xf8, 0xde, 0x96, 0xd6, 0x14,
    0xa4, 0xd0, 0x41, 0xe6, 0x4a, 0x48, 0x21, 0x04, 0x20, 0xc3, 0x20, 0xe4, 0x21, 0x04, 0x39, 0xe8,
    0x18, 0xc3, 0x18, 0xa2, 0x20, 0xe3, 0x21, 0x04, 0x18, 0xc3, 0x10, 0x82, 0x21, 0x24, 0xa4, 0xb0,
    0xff, 0xdd, 0xff, 0xfd, 0xff, 0xfd, 0xff, 0xfe, 0xff, 0xfe, 0xff, 0xfe, 0xff, 0xfe, 0xff, 0xfe,
    0xf7, 0xbc, 0xf7, 0x9b, 0xf7, 0x9b, 0xef, 0x5a, 0xde, 0xd7, 0xe7, 0x18, 0xde, 0x96, 0xcd, 0xf4,
    0xb5, 0x52, 0x5a, 0xa9, 0x52, 0x68, 0x29, 0x44, 0x18, 0xc3, 0x20, 0xe4, 0x21, 0x04, 0x31, 0x86,
    0x18, 0xc3, 0x18, 0xa3, 0x20, 0xe3, 0x21, 0x04, 0x18, 0xc3, 0x18, 0xc3, 0x20, 0xe4, 0x5a, 0x68,
    0xf7, 0x5a, 0xff, 0xfd, 0xff, 0xfd, 0xff, 0xfd, 0xff, 0xfd, 0xff, 0xfe, 0xff, 0xfe, 0xff, 0xfe,
    0xf7, 0x9b, 0xf7, 0x9b, 0xf7, 0x7b, 0xef, 0x39, 0xde, 0xb7, 0xe7, 0x18, 0xde, 0xb6, 0xcd, 0xf3,
    0xb5, 0x11, 0x4a, 0x27, 0x31, 0x65, 0x18, 0xa2, 0x10, 0x82, 0x10, 0xa2, 0x10, 0xa2, 0x18, 0xc3,
    0x39, 0x84, 0x29, 0x24, 0x18, 0xc3, 0x20, 0xe3, 0x20, 0xe4, 0x18, 0xc3, 0x29, 0x24, 0x39, 0x86,
    0xc5, 0xf4, 0xff, 0xfd, 0xff, 0xdd, 0xff, 0xfd, 0xff, 0xfd, 0xff, 0xfd, 0xff, 0xfd, 0xff, 0xfd,
    0xef, 0x7b, 0xf7, 0x7a, 0xef, 0x5a, 0xe7, 0x18, 0xde, 0x96, 0xe6, 0xf7, 0xe6, 0xb7, 0xcd, 0xb3,
    0x7b, 0x6b, 0x31, 0x44, 0x41, 0xe6, 0x18, 0xc3, 0x18, 0xc3, 0x18, 0xa2, 0x10, 0x82, 0x52, 0x46,
    0x73, 0x6a, 0x6a, 0xe9, 0x18, 0xa2, 0x18, 0xa2, 0x10, 0xa2, 0x18, 0xc3, 0x21, 0x04, 0x29, 0x45,
    0x94, 0x2e, 0xff, 0xbb, 0xff, 0xfd, 0xff, 0xfd, 0xff, 0xdd, 0xff, 0xdd, 0xff, 0xfd, 0xff, 0xfd,
    0xef, 0x7b, 0xf7, 0x9b, 0xef, 0x7a, 0xef, 0x39, 0xde, 0x96, 0xe6, 0xd7, 0xe6, 0xd7, 0xb5, 0x51,
    0x39, 0x85, 0x39, 0xa5, 0x6b, 0x4a, 0x5a, 0xa8, 0x20, 0xe3, 0x18, 0xe3, 0x18, 0xc2, 0x4a, 0x47,
    0x62, 0xc8, 0x31, 0x44, 0x10, 0x82, 0x10, 0xa2, 0x18, 0xa2, 0x10, 0xa2, 0x18, 0xe3, 0x21, 0x04,
    0x52, 0x69, 0xe6, 0xd8, 0xff, 0xdc, 0xff, 0xfd, 0xff, 0xfd, 0xff, 0xfd, 0xff, 0xfd, 0xff, 0xdd,
    0xef, 0x5a, 0xef, 0x5a, 0xef, 0x5a, 0xe6, 0xf8, 0xde, 0x76, 0xde, 0x96, 0xe6, 0xb6, 0xb5, 0x11,
    0x39, 0xa5, 0x20, 0xe3, 0x49, 0xe5, 0x39, 0xa5, 0x21, 0x04, 0x20, 0xe4, 0x18, 0xc3, 0x18, 0xa2,
    0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x10, 0x82, 0x18, 0xc3, 0x21, 0x04, 0x18, 0xa3, 0x20, 0xe4,
    0x4a, 0x49, 0x9c, 0x90, 0xf7, 0x9b, 0xff, 0xdc, 0xff, 0xfc, 0xff, 0xfd, 0xff, 0xfd, 0xff, 0xfd,
    0xf7, 0x7b, 0xf7, 0x9b, 0xef, 0x7a, 0xe7, 0x18, 0xde, 0x96, 0xde, 0x76, 0xe6, 0x96, 0xac, 0xf0,
    0x39, 0x85, 0x20, 0xe3, 0x18, 0xc3, 0x29, 0x44, 0x52, 0x89, 0x21, 0x45, 0x18, 0xa3, 0x10, 0x82,
    0x10, 0x82, 0x10, 0x62, 0x10, 0x82, 0x10, 0x62, 0x10, 0x82, 0x18, 0xe3, 0x29, 0x45, 0x31, 0xa7,
    0x4a, 0x69, 0x52, 0x8a, 0xc5, 0xf5, 0xff, 0xbb, 0xff, 0xdc, 0xff, 0xdc, 0xff, 0xdc, 0xff, 0xfc,
    0xef, 0x5a, 0xf7, 0x7a, 0xef, 0x5a, 0xe6, 0xd8, 0xd6, 0x55, 0xd6, 0x35, 0xde, 0x76, 0xbd, 0x72,
    0x52, 0x27, 0x31, 0x44, 0x20, 0xe3, 0x42, 0x07, 0x41, 0xe7, 0x21, 0x25, 0x18, 0xa2, 0x18, 0xa2,
    0x18, 0xc3, 0x21, 0x45, 0x29, 0x86, 0x29, 0x65, 0x31, 0x86, 0x29, 0x65, 0x21, 0x04, 0x18, 0xe3,
    0x39, 0xe8, 0x42, 0x28, 0x8c, 0x0f, 0xf7, 0x7a, 0xff, 0xdb, 0xff, 0xdc, 0xff, 0xdc, 0xff, 0xdc,
    0xf7, 0x7b, 0xf7, 0x9b, 0xef, 0x7a, 0xe6, 0xf8, 0xde, 0x76, 0xd6, 0x35, 0xde, 0x76, 0xcd, 0xb3,
    0x73, 0x2a, 0x29, 0x24, 0x39, 0xa6, 0x29, 0x44, 0x21, 0x04, 0x18, 0xc3, 0x10, 0xa2, 0x10, 0xa2,
    0x21, 0x24, 0x31, 0xa7, 0x4a, 0x6a, 0x42, 0x49, 0x31, 0xc7, 0x3a, 0x08, 0x3a, 0x09, 0x31, 0xc7,
    0x31, 0xc7, 0x39, 0xa7, 0x5a, 0xeb, 0xe6, 0xb7, 0xff, 0xbb, 0xff, 0xbb, 0xff, 0xbb, 0xff, 0xdb,
    0xef, 0x59, 0xf7, 0x9a, 0xef, 0x5a, 0xde, 0xd7, 0xd6, 0x55, 0xd6, 0x14, 0xde, 0x55, 0xcd, 0xd3,
    0xa4, 0xaf, 0x52, 0x68, 0x5a, 0x89, 0x31, 0x65, 0x21, 0x04, 0x4a, 0x69, 0x29, 0x45, 0x18, 0xc3,
    0x21, 0x24, 0x4a, 0x8a, 0x5a, 0xec, 0x52, 0xcb, 0x42, 0x49, 0x39, 0xe8, 0x39, 0xe8, 0x4a, 0xab,
    0x42, 0x29, 0x42, 0x29, 0x52, 0xcb, 0xb5, 0x74, 0xff, 0x7a, 0xff, 0x9b, 0xff, 0x9b, 0xff, 0x9b,
    0xff, 0xbb, 0xff, 0xfd, 0xef, 0x9b, 0xe6, 0xd8, 0xd6, 0x56, 0xcd, 0xf4, 0xde, 0x35, 0xcd, 0xd3,
    0xc5, 0x92, 0x94, 0x2e, 0x6b, 0x4c, 0x5a, 0xa9, 0x5a, 0x89, 0x29, 0x44, 0x18, 0xe3, 0x18, 0xe4,
    0x31, 0xc7, 0x42, 0x49, 0x4a, 0x6a, 0x42, 0x29, 0x52, 0xcb, 0x52, 0xab, 0x4a, 0xac, 0x4a, 0x8b,
    0x42, 0x6a, 0x31, 0xc7, 0x39, 0xe8, 0x94, 0x71, 0xf7, 0x59, 0xff, 0x7a, 0xff, 0x9a, 0xff, 0x9a,
    0xff, 0xbc, 0xff, 0xfd, 0xf7, 0x9c, 0xe6, 0xf8, 0xd6, 0x56, 0xcd, 0xd3, 0xd6, 0x35, 0xcd, 0xf4,
    0xc5, 0xb3, 0x94, 0x6f, 0x6b, 0x0a, 0x62, 0xea, 0x7b, 0xad, 0x6b, 0x2b, 0x29, 0x23, 0x21, 0x03,
    0x29, 0x24, 0x42, 0x08, 0x63, 0x0c, 0x6b, 0x8e, 0x84, 0x30, 0x8c, 0xb3, 0x8c, 0xd4, 0x53, 0x0d,
    0x31, 0xe8, 0x31, 0x86, 0x39, 0xe8, 0x7b, 0xcf, 0xee, 0xf8, 0xf7, 0x59, 0xf7, 0x79, 0xf7, 0x59,
    0xff, 0xdc, 0xff, 0xdc, 0xef, 0x7b, 0xe6, 0xd7, 0xd6, 0x35, 0xc5, 0xb2, 0xd6, 0x34, 0xcd, 0xd3,
    0xc5, 0xb3, 0x8b, 0xed, 0x62, 0xea, 0x8c, 0x4f, 0x7b, 0xad, 0x73, 0x8d, 0x73, 0x6c, 0x62, 0xca,
    0x73, 0x6c, 0x84, 0x0f, 0x8c, 0x71, 0x9c, 0xd3, 0x9d, 0x14, 0xa5, 0x76, 0x84, 0x93, 0x31, 0xe8,
    0x42, 0x6a, 0x42, 0x29, 0x31, 0xa7, 0x73, 0x8d, 0xe6, 0xd7, 0xf7, 0x38, 0xf7, 0x39, 0xf7, 0x38,
    0xef, 0x18, 0xef, 0x18, 0xde, 0x96, 0xd6, 0x55, 0xd6, 0x15, 0xc5, 0xb3, 0xd5, 0xf4, 0xcd, 0xf3,
    0xc5, 0xb3, 0x83, 0x8c, 0x62, 0xea, 0x94, 0xb1, 0x9c, 0xd1, 0x94, 0x90, 0x94, 0x70, 0x94, 0x70,
    0x94, 0x90, 0x94, 0xb1, 0x9c, 0xd2, 0xa5, 0x13, 0xa5, 0x55, 0xa5, 0x55, 0x73, 0xf0, 0x21, 0x45,
    0x21, 0x25, 0x42, 0x29, 0x39, 0xe8, 0x73, 0xaf, 0xd6, 0x76, 0xef, 0x18, 0xef, 0x18, 0xee, 0xf8,
    0xde, 0xb7, 0xde, 0x76, 0xd6, 0x35, 0xd6, 0x14, 0xcd, 0xf4, 0xc5, 0x92, 0xcd, 0xf3, 0xcd, 0xf4,
    0xc5, 0x92, 0x9c, 0x90, 0x9c, 0xb1, 0x9c, 0xb1, 0x9c, 0xd1, 0x9c, 0xd1, 0x9c, 0xb1, 0x94, 0xb1,
    0x9c, 0xb1, 0x9c, 0xf2, 0x9c, 0xf2, 0xa5, 0x13, 0xa5, 0x13, 0x94, 0xd2, 0x7b, 0xcf, 0x31, 0xc7,
    0x29, 0x66, 0x21, 0x24, 0x39, 0xc7, 0x63, 0x2d, 0x8c, 0x51, 0xd6, 0x56, 0xe6, 0xd7, 0xe6, 0xb7,
    0xd6, 0x56, 0xd6, 0x56, 0xd6, 0x35, 0xd6, 0x35, 0xce, 0x14, 0xc5, 0x92, 0xcd, 0xd3, 0xcd, 0xd3,
    0xc5, 0x92, 0x94, 0x4e, 0x84, 0x0f, 0x9c, 0xd1, 0x9c, 0xd1, 0x9c, 0xd1, 0x9c, 0xd1, 0x9c, 0xd1,
    0x9c, 0xd1, 0x9c, 0xf2, 0x9d, 0x12, 0xa5, 0x13, 0xa5, 0x34, 0x84, 0x51, 0x5a, 0xec, 0x21, 0x25,
    0x18, 0xe4, 0x21, 0x04, 0x39, 0xe8, 0x5b, 0x2e, 0x52, 0xab, 0x84, 0x0f, 0xd6, 0x35, 0xde, 0x76,
    0xd6, 0x35, 0xce, 0x15, 0xcd, 0xf4, 0xcd, 0xf4, 0xc5, 0xd3, 0xbd, 0x51, 0xc5, 0xb2, 0xcd, 0xd3,
    0xc5, 0x72, 0xac, 0xcf, 0x62, 0xc9, 0x7b, 0xce, 0x8c, 0x50, 0x94, 0xb0, 0x9c, 0xd1, 0x9c, 0xd1,
    0x9c, 0xd1, 0xa4, 0xf2, 0x9c, 0xf2, 0x9c, 0xd2, 0x84, 0x30, 0x42, 0x49, 0x18, 0xc3, 0x18, 0xe4,
    0x18, 0xe3, 0x29, 0x24, 0x42, 0x29, 0x52, 0xed, 0x3a, 0x09, 0x4a, 0x49, 0x8c, 0x4f, 0xce, 0x15
};

const __flash Bitmap bitmaps[] = {
    {32, 26, SPACE_GREY4, LINUS_GREY4_DATA},
    {32, 26, SPACE_RGB16, LINUS_RGB16_DATA}
};
