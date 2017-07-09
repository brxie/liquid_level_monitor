/*
 * font.h
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
#pragma once
#ifndef __FONT_H__
#define __FONT_H__
#include "stm8s.h"

#define LTR_WIDTH	(6)
#define BIG_FONT_XSIZE  (16)
#define BIG_FONT_YSIZE  (2)
#define BIG_FONT_LEN    BIG_FONT_XSIZE * BIG_FONT_YSIZE

uint8_t *letter(uint8_t koi8);
uint8_t *big_symbol(uint8_t koi8);

#endif // __FONT_H__
