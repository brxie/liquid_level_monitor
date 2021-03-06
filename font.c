/*
 * font.c - russian font
 *
 * Copyright 2015 Edward V. Emelianoff <eddy@sao.ru, edward.emelianoff@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 */

#include "font.h"

const uint8_t rusfont [] = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00,// 32 [0x20] -
	0x00, 0x00, 0x5F, 0x00, 0x00, 0x00,// 33 [0x21] - !
	0x00, 0x07, 0x00, 0x07, 0x00, 0x00,// 34 [0x22] - "
	0x14, 0x7F, 0x14, 0x7F, 0x14, 0x00,// 35 [0x23] - #
	0x24, 0x2A, 0x7F, 0x2A, 0x12, 0x00,// 36 [0x24] - $
	0x23, 0x13, 0x08, 0x64, 0x62, 0x00,// 37 [0x25] - %
	0x36, 0x49, 0x55, 0x22, 0x50, 0x00,// 38 [0x26] - &
	0x00, 0x05, 0x03, 0x00, 0x00, 0x00,// 39 [0x27] - '
	0x00, 0x1C, 0x22, 0x41, 0x00, 0x00,// 40 [0x28] - (
	0x00, 0x41, 0x22, 0x1C, 0x00, 0x00,// 41 [0x29] - )
	0x08, 0x2A, 0x1C, 0x2A, 0x08, 0x00,// 42 [0x2a] - *
	0x08, 0x08, 0x3E, 0x08, 0x08, 0x00,// 43 [0x2b] - +
	0x00, 0x50, 0x30, 0x00, 0x00, 0x00,// 44 [0x2c] - ,
	0x08, 0x08, 0x08, 0x08, 0x08, 0x00,// 45 [0x2d] - -
	0x00, 0x60, 0x60, 0x00, 0x00, 0x00,// 46 [0x2e] - .
	0x20, 0x10, 0x08, 0x04, 0x02, 0x00,// 47 [0x2f] - /
	0x3E, 0x51, 0x49, 0x45, 0x3E, 0x00,// 48 [0x30] - 0
	0x00, 0x42, 0x7F, 0x40, 0x00, 0x00,// 49 [0x31] - 1
	0x42, 0x61, 0x51, 0x49, 0x46, 0x00,// 50 [0x32] - 2
	0x21, 0x41, 0x45, 0x4B, 0x31, 0x00,// 51 [0x33] - 3
	0x18, 0x14, 0x12, 0x7F, 0x10, 0x00,// 52 [0x34] - 4
	0x27, 0x45, 0x45, 0x45, 0x39, 0x00,// 53 [0x35] - 5
	0x3C, 0x4A, 0x49, 0x49, 0x30, 0x00,// 54 [0x36] - 6
	0x01, 0x71, 0x09, 0x05, 0x03, 0x00,// 55 [0x37] - 7
	0x36, 0x49, 0x49, 0x49, 0x36, 0x00,// 56 [0x38] - 8
	0x06, 0x49, 0x49, 0x29, 0x1E, 0x00,// 57 [0x39] - 9
	0x00, 0x36, 0x36, 0x00, 0x00, 0x00,// 58 [0x3a] - :
	0x00, 0x56, 0x36, 0x00, 0x00, 0x00,// 59 [0x3b] - ;
	0x00, 0x08, 0x14, 0x22, 0x41, 0x00,// 60 [0x3c] - <
	0x14, 0x14, 0x14, 0x14, 0x14, 0x00,// 61 [0x3d] - =
	0x41, 0x22, 0x14, 0x08, 0x00, 0x00,// 62 [0x3e] - >
	0x02, 0x01, 0x51, 0x09, 0x06, 0x00,// 63 [0x3f] - ?
	0x32, 0x49, 0x79, 0x41, 0x3E, 0x00,// 64 [0x40] - @
	0x7E, 0x11, 0x11, 0x11, 0x7E, 0x00,// 65 [0x41] - A
	0x7F, 0x49, 0x49, 0x49, 0x36, 0x00,// 66 [0x42] - B
	0x3E, 0x41, 0x41, 0x41, 0x22, 0x00,// 67 [0x43] - C
	0x7F, 0x41, 0x41, 0x22, 0x1C, 0x00,// 68 [0x44] - D
	0x7F, 0x49, 0x49, 0x49, 0x41, 0x00,// 69 [0x45] - E
	0x7F, 0x09, 0x09, 0x01, 0x01, 0x00,// 70 [0x46] - F
	0x3E, 0x41, 0x41, 0x51, 0x32, 0x00,// 71 [0x47] - G
	0x7F, 0x08, 0x08, 0x08, 0x7F, 0x00,// 72 [0x48] - H
	0x00, 0x41, 0x7F, 0x41, 0x00, 0x00,// 73 [0x49] - I
	0x20, 0x40, 0x41, 0x3F, 0x01, 0x00,// 74 [0x4a] - J
	0x7F, 0x08, 0x14, 0x22, 0x41, 0x00,// 75 [0x4b] - K
	0x7F, 0x40, 0x40, 0x40, 0x40, 0x00,// 76 [0x4c] - L
	0x7F, 0x02, 0x04, 0x02, 0x7F, 0x00,// 77 [0x4d] - M
	0x7F, 0x04, 0x08, 0x10, 0x7F, 0x00,// 78 [0x4e] - N
	0x3E, 0x41, 0x41, 0x41, 0x3E, 0x00,// 79 [0x4f] - O
	0x7F, 0x09, 0x09, 0x09, 0x06, 0x00,// 80 [0x50] - P
	0x3e, 0x41, 0x51, 0x21, 0xde, 0x00,// 81 [0x51] - Q
	0x7F, 0x09, 0x19, 0x29, 0x46, 0x00,// 82 [0x52] - R
	0x46, 0x49, 0x49, 0x49, 0x31, 0x00,// 83 [0x53] - S
	0x01, 0x01, 0x7F, 0x01, 0x01, 0x00,// 84 [0x54] - T
	0x3F, 0x40, 0x40, 0x40, 0x3F, 0x00,// 85 [0x55] - U
	0x1F, 0x20, 0x40, 0x20, 0x1F, 0x00,// 86 [0x56] - V
	0x7F, 0x20, 0x18, 0x20, 0x7F, 0x00,// 87 [0x57] - W
	0x63, 0x14, 0x08, 0x14, 0x63, 0x00,// 88 [0x58] - X
	0x03, 0x04, 0x78, 0x04, 0x03, 0x00,// 89 [0x59] - Y
	0x61, 0x51, 0x49, 0x45, 0x43, 0x00,// 90 [0x5a] - Z
	// 0x00, 0x00, 0x7F, 0x41, 0x41, 0x00,// 91 [0x5b] - [
	// 0x02, 0x04, 0x08, 0x10, 0x20, 0x00,// 92 [0x5c] - "\"
	// 0x41, 0x41, 0x7F, 0x00, 0x00, 0x00,// 93 [0x5d] - ]
	// 0x04, 0x02, 0x01, 0x02, 0x04, 0x00,// 94 [0x5e] - ^
	// 0x40, 0x40, 0x40, 0x40, 0x40, 0x00,// 95 [0x5f] - _
	// 0x00, 0x01, 0x02, 0x04, 0x00, 0x00,// 96 [0x60] - `
	// 0x20, 0x54, 0x54, 0x54, 0x78, 0x00,// 97 [0x61] - a
	// 0x7F, 0x48, 0x44, 0x44, 0x38, 0x00,// 98 [0x62] - b
	// 0x38, 0x44, 0x44, 0x44, 0x20, 0x00,// 99 [0x63] - c
	// 0x38, 0x44, 0x44, 0x48, 0x7F, 0x00,//100 [0x64] - d
	// 0x38, 0x54, 0x54, 0x54, 0x18, 0x00,//101 [0x65] - e
	// 0x00, 0x08, 0xfe, 0x09, 0x02, 0x00,//102 [0x66] - f
	// 0x18, 0xa4, 0xa4, 0x94, 0x78, 0x00,//103 [0x67] - g
	// 0x7F, 0x08, 0x04, 0x04, 0x78, 0x00,//104 [0x68] - h
	// 0x00, 0x44, 0x7D, 0x40, 0x00, 0x00,//105 [0x69] - i
	// 0x40, 0x80, 0x84, 0x7d, 0x00, 0x00,//106 [0x6a] - j
	// 0x00, 0x7F, 0x10, 0x28, 0x44, 0x00,//107 [0x6b] - k
	// 0x00, 0x41, 0x7F, 0x40, 0x00, 0x00,//108 [0x6c] - l
	// 0x7C, 0x04, 0x18, 0x04, 0x78, 0x00,//109 [0x6d] - m
	// 0x7C, 0x08, 0x04, 0x04, 0x78, 0x00,//110 [0x6e] - n
	// 0x38, 0x44, 0x44, 0x44, 0x38, 0x00,//111 [0x6f] - o
	// 0xfc, 0x28, 0x24, 0x24, 0x18, 0x00,//112 [0x70] - p
	// 0x18, 0x24, 0x24, 0x28, 0xfc, 0x00,//113 [0x71] - q
	// 0x7C, 0x08, 0x04, 0x04, 0x08, 0x00,//114 [0x72] - r
	// 0x48, 0x54, 0x54, 0x54, 0x20, 0x00,//115 [0x73] - s
	// 0x04, 0x3F, 0x44, 0x40, 0x20, 0x00,//116 [0x74] - t
	// 0x3C, 0x40, 0x40, 0x20, 0x7C, 0x00,//117 [0x75] - u
	// 0x1C, 0x20, 0x40, 0x20, 0x1C, 0x00,//118 [0x76] - v
	// 0x3C, 0x40, 0x30, 0x40, 0x3C, 0x00,//119 [0x77] - w
	// 0x44, 0x28, 0x10, 0x28, 0x44, 0x00,//120 [0x78] - x
	// 0x0C, 0x50, 0x50, 0x50, 0x3C, 0x00,//121 [0x79] - y
	// 0x44, 0x64, 0x54, 0x4C, 0x44, 0x00,//122 [0x7a] - z
	// 0x00, 0x08, 0x36, 0x41, 0x00, 0x00,//123 [0x7b] - {
	// 0x00, 0x00, 0x7F, 0x00, 0x00, 0x00,//124 [0x7c] - |
	// 0x00, 0x41, 0x36, 0x08, 0x00, 0x00,//125 [0x7d] - }
	// 0x08, 0x04, 0x08, 0x10, 0x08, 0x00,//126 [0x7e] - ~
	// 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,//127 [0x7f] -
};

const uint8_t bigfont [] = {
	0x00,0xE0,0xF8,0xFC,0xFE,0x1E,0x07,0x07,0x07,0x07,0x1E,0xFE,0xFC,0xF8,0xF0,0x00,0x00,0x07,0x0F,0x3F,0x3F,0x7C,0x70,0x70,0x70,0x70,0x7C,0x3F,0x1F,0x1F,0x07,0x00,/*0*/
	0x00,0x00,0x00,0x06,0x07,0x07,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x7F,0x7F,0x7F,0x7F,0x00,0x00,0x00,0x00,0x00,0x00,/*1*/
	0x00,0x38,0x3C,0x3E,0x3E,0x0F,0x07,0x07,0x07,0xCF,0xFF,0xFE,0xFE,0x38,0x00,0x00,0x00,0x40,0x40,0x60,0x70,0x78,0x7C,0x7E,0x7F,0x77,0x73,0x71,0x70,0x70,0x00,0x00,/*2*/
	0x00,0x18,0x1C,0x1E,0x1E,0x0F,0xC7,0xC7,0xE7,0xFF,0xFE,0xBE,0x9C,0x00,0x00,0x00,0x00,0x0C,0x1C,0x3C,0x3C,0x78,0x70,0x70,0x70,0x79,0x7F,0x3F,0x1F,0x0F,0x00,0x00,/*3*/
	0x00,0x00,0x80,0xC0,0xE0,0x70,0x38,0x1C,0x1E,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x06,0x07,0x07,0x07,0x06,0x06,0x06,0x06,0x06,0x7F,0x7F,0x7F,0x7F,0x06,0x06,0x00,/*4*/
	0x00,0x00,0x00,0x00,0xF0,0xFF,0xFF,0xFF,0xE7,0xE7,0xE7,0xE7,0xC7,0x87,0x00,0x00,0x00,0x00,0x38,0x78,0x71,0x70,0x70,0x70,0x70,0x70,0x39,0x3F,0x3F,0x1F,0x0F,0x00,/*5*/
	0x00,0x80,0xE0,0xF0,0xF8,0xFC,0x7F,0x7F,0x6F,0x67,0xE1,0xE1,0xC0,0x80,0x00,0x00,0x00,0x0F,0x1F,0x3F,0x3F,0x78,0x70,0x70,0x70,0x70,0x78,0x3F,0x3F,0x1F,0x0F,0x00,/*6*/
	0x00,0x07,0x07,0x07,0x07,0x07,0xC7,0xE7,0xF7,0xFF,0x7F,0x3F,0x1F,0x07,0x03,0x01,0x00,0x20,0x38,0x7C,0x7E,0x3F,0x0F,0x07,0x03,0x00,0x00,0x00,0x00,0x00,0x00,0x00,/*7*/
	0x00,0x00,0x00,0x1C,0xBE,0xFE,0xFF,0xE7,0xC3,0xC3,0xE7,0xFF,0xFE,0xBE,0x1C,0x00,0x00,0x00,0x0E,0x3F,0x3F,0x7F,0x71,0x60,0x60,0x60,0x71,0x7F,0x3F,0x3F,0x0F,0x00,/*8*/
	0x00,0x78,0xFC,0xFE,0xFE,0x8F,0x07,0x07,0x07,0x07,0x8F,0xFE,0xFE,0xFC,0xF8,0x00,0x00,0x00,0x00,0x01,0x43,0x43,0x73,0x7B,0x7F,0x7F,0x1F,0x0F,0x07,0x03,0x00,0x00,/*9*/
};

/**
 * Return letter array
 */
uint8_t *letter(uint8_t koi8){
	uint16_t idx;
	if(koi8 < 32) koi8 = 32;
	idx = (koi8 - 32) * LTR_WIDTH;
	return &rusfont[idx];
}

/**
 * Return number array
 */
uint8_t *big_symbol(uint8_t koi8){
	uint16_t idx;
	if(koi8 < 48) koi8 = 48;
	idx = (koi8 - 48) * BIG_FONT_LEN;
	return &bigfont[idx];
}
