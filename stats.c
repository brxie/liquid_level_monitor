#include "stats.h"

static uint16_t adc_min = 335;
static uint16_t adc_max = 394;


uint16_t get_liquid_level() {
    uint16_t adc_res = 0;
    uint32_t read_sum = 0;
    uint16_t i;
    float step = 100 / (float)(adc_max - adc_min);
    /* get more stable results doing multiple measurement */
    for ( i = 0; i < 1000; i++ ) {
        read_sum += adc_read();
    }
    adc_res = read_sum / 1000;
    return (adc_res - adc_min) * step;
}

/* debug purposes */
uint16_t get_adc_val() {
    return adc_read();
}

void init_stats() {
    adc_init();
}

void set_adc_min(uint16_t val) {
    adc_min = val;
}

uint16_t get_adc_min() {
    return adc_min;
}

void set_adc_max(uint16_t val) {
    adc_max = val;
}

uint16_t get_adc_max() {
    return adc_max;
}