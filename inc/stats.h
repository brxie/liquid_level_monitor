#ifndef __ADC_H__
#define __ADC_H__

#include "adc.h"
#include "stm8s.h"

static uint16_t adc_min;
static uint16_t adc_max;

uint16_t get_liquid_level();
void init_stats();
void set_adc_min(uint16_t val);
uint16_t get_adc_min();
void set_adc_max(uint16_t val);
uint16_t get_adc_max();


#endif