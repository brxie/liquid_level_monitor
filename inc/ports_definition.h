/*
 * ports_definition.h - definition of ports pins & so on
 *
 * Copyright 2014 Edward V. Emelianov <eddy@sao.ru, edward.emelianoff@gmail.com>
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
#include "stm8s.h"
#include "stm8s_gpio.h"
#pragma once
#ifndef __PORTS_DEFINITION_H__
#define __PORTS_DEFINITION_H__

// SPI pins: SCK - PC5, MOSI - PC6, MISO - PC7
#define SPI_PORT		GPIOC
#define SPI_SCK_PIN		GPIO_PIN_5
#define SPI_MOSI_PIN	GPIO_PIN_6
#define SPI_MISO_PIN	GPIO_PIN_7

// LCD5110 pins: ~RST is PD2, ~CE is PD1, D/~C is PD0
#define LCD_PORT		GPIOD
#define LCD_RST_PIN		GPIO_PIN_1
#define LCD_CE_PIN		GPIO_PIN_4
#define LCD_DC_PIN		GPIO_PIN_2
/* here are functions & macros for changing command pins state:
 *   SET_DC()    - set D/~C pin high (data)
 *   CLEAR_DC()  - clear D/~C (command)
 *   CHIP_EN()   - clear ~SCE
 *   CHIP_DIS()  - set ~SCE (disable chip)
 *   CLEAR_RST() - set 1 on RST pin (SHOULD BE 0 AT START)
 */
#define SET_DC()		(GPIOD -> ODR |= LCD_DC_PIN)
#define CLEAR_DC()		(GPIOD -> ODR &= ~LCD_DC_PIN)
#define CHIP_EN()		(GPIOD -> ODR &= ~LCD_CE_PIN)
#define CHIP_DIS()		(GPIOD -> ODR |= LCD_CE_PIN)
#define CLEAR_RST()		(GPIOD -> ODR |= LCD_RST_PIN)
#define LCD_RST()		(GPIOD -> ODR &= ~LCD_RST_PIN)

#endif // __PORTS_DEFINITION_H__
