#include "adc.h"
#include "stats.h"

static uint16_t tank_cap = 150;
float adc_multipl = 0.315;
uint16_t adc_offset = 670;
extern uint8_t sett_cusr_pos;
uint8_t sett_step_mode = 0;
enum SETT_VAL {CAP, MULTIPL, ADC_OFF};
enum SETT_VAL_STEP_MODE {ADD, SUBTRACT};

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
    uint16_t res = ((adc_offset - get_adc_val()) * adc_multipl);
    /* aviod huge values which may cause crash caused by integer overflow */
    res &= ~(0x0f << 12);
    return res;
}

uint16_t get_space_used() {
    uint16_t res = tank_cap - ((adc_offset - get_adc_val()) * adc_multipl);
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

uint16_t get_adc_multipl() {
    return adc_multipl * 1000;
}

void set_adc_multipl(uint16_t multipl) {
    if (multipl / 1000 > 9999) {
        return;
    }
    adc_multipl = (float)multipl / 1000;
}

uint16_t get_adc_offset() {
    return adc_offset;
}

void set_adc_offset(uint16_t offset) {
    if (offset > 9999) {
        return;
    }
    adc_offset = offset;
}

void toggle_sett_step_mode() {
    if (sett_step_mode == 0) {
        sett_step_mode = 1;
        return;
    }
    sett_step_mode = 0;
}

void set_activ_sett_val(uint16_t val) {
    switch (sett_cusr_pos) {
    case CAP:
        set_tank_cap(val);
        break;
    case MULTIPL:
        set_adc_multipl(val);
        break;
    case ADC_OFF:
        set_adc_offset(val);
        break;
    }
}

uint16_t get_activ_sett_val() {
    switch (sett_cusr_pos) {
    case CAP:
        return get_tank_cap();
    case MULTIPL:
        return get_adc_multipl();
    case ADC_OFF:
        return get_adc_offset();
    }
}

void step_activ_sett_val() {
    switch (sett_step_mode) {
    case ADD:
        set_activ_sett_val(get_activ_sett_val() + 1);
        break;
    case SUBTRACT:
        set_activ_sett_val(get_activ_sett_val() - 1);
        break;
    }
}