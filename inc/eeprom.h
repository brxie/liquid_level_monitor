#ifndef __EEPROM_H__
#define __EEPROM_H__
#include "stm8s.h"
#include "stm8s_flash.h"

void eeprom_write_page(uint16_t addr, uint8_t *src, uint8_t count);
void eeprom_read_page(uint16_t addr, uint8_t * dest, uint8_t count);
// uint8_t eeprom_read_byte(uint16_t addr);

#endif