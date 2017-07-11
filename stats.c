#include "adc.h"
#include "stats.h"

static uint16_t tank_cap = 17;
float adc_step = 0.315;
uint16_t adc_start = 670;


uint16_t get_percent_fill() {
    float step = 100 / (float)tank_cap;
    return (tank_cap - get_space_left()) * step;
}

uint16_t get_adc_val() {
    uint16_t i = 0;
    uint32_t read_sum = 0;
    for ( i = 0; i < 1000; i++ ) {
        read_sum += adc_read();
    }
    return read_sum / 1000;
}

uint16_t get_space_left() {
    uint16_t res = ((adc_start - get_adc_val()) * adc_step);
    /* aviod huge values which may cause crash caused by integer overflow */
    res &= ~(0x0f << 12);
    return res;
}

uint16_t get_space_used() {
    uint16_t res = tank_cap - ((adc_start - get_adc_val()) * adc_step);
    /* aviod huge values which may cause crash caused by integer overflow */
    res &= ~(0x0f << 12);
    return res;
}

void init_stats() {
    adc_init();
}

uint16_t get_tank_cap() {
    return tank_cap;
}

void set_tank_cap(uint16_t cap) {
    if (cap > 999) {
        return;
    }
    tank_cap = cap;
}