#ifndef __ADC_H__
#define __ADC_H__

#include "adc.h"
#include "stm8s.h"

static uint16_t adc_min;
static uint16_t adc_max;

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


#endif