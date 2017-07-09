#ifndef __ADC_H__
#define __ADC_H__
#include "stm8s.h"
#include "stm8s_adc1.h"

void adc_init();
uint16_t adc_read();

#endif