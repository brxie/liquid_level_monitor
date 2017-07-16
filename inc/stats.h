#ifndef __ADC_H__
#define __ADC_H__

#include "adc.h"
#include "eeprom.h"
#include "stm8s.h"

#define DEFAULT_TANK_CAPACITY ((uint8_t)150)
#define DEFAULT_ADC_MULTIPLER ((uint16_t)315)
#define DEFAULT_ADC_OFFSET ((uint16_t)670)

#define TANK_CAPACITY_EEPROM_ADDRESS 0
#define ADC_MULTIPLER_EEPROM_ADDRESS 2
#define ADC_OFFSET_EEPROM_ADDRESS 4

uint16_t get_percent_fill();
uint16_t get_adc_val();
uint16_t get_space_left();
uint16_t get_space_used();
void init_stats();
uint16_t get_tank_cap();
void set_tank_cap(uint16_t cap);
uint16_t get_adc_multipl();
void set_adc_multipl(uint16_t multipl);
uint16_t get_adc_offset();
void set_adc_offset(uint16_t margin);
void toggle_sett_step_mode();
void set_activ_sett_val(uint16_t val);
uint16_t get_activ_sett_val();
void step_activ_sett_val();
void persist_settings_in_eeprom();
void read_settings_from_eeprom();
void restore_default_settings();

#endif