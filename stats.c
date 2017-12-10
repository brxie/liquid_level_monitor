#include "stats.h"

uint16_t tank_cap;
uint16_t adc_multipl;
uint16_t adc_offset;
extern uint8_t sett_cusr_pos;
uint8_t sett_step_mode = 0;
enum SETT_VAL {CAP, MULTIPL, ADC_OFF};
enum SETT_VAL_STEP_MODE {ADD, SUBTRACT};

uint16_t get_percent_fill() {
    float step = 100 / (float)tank_cap;
    uint8_t res;
    res = (tank_cap - get_space_left()) * step;
    if (res > 100) {
        return 100;
    }
    return res;
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
    int16_t res = tank_cap - get_space_used();
    if (res > tank_cap) {
        res = tank_cap;
    }
    return res;
}

uint16_t get_space_used() {
    uint16_t res = 0;
    int16_t adc_act_val = get_adc_val() - adc_offset;

    res = ((uint16_t)adc_act_val * ((float)adc_multipl / 100));
    if (res > tank_cap) {
        res = tank_cap;
    }
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
    return adc_multipl;
}

void set_adc_multipl(uint16_t multipl) {
    if (multipl > 9999) {
        return;
    }
    adc_multipl = multipl;
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
        return tank_cap;
    case MULTIPL:
        return adc_multipl;
    case ADC_OFF:
        return adc_offset;
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

void persist_settings_in_eeprom() {
    uint8_t eeprom_buff[2];

    eeprom_buff[0]=tank_cap & 0xff;
    eeprom_buff[1]=(tank_cap >> 8);
    eeprom_write_page(TANK_CAPACITY_EEPROM_ADDRESS, eeprom_buff, 2);

    eeprom_buff[0]=adc_multipl & 0xff;
    eeprom_buff[1]=(adc_multipl >> 8);
    eeprom_write_page(ADC_MULTIPLER_EEPROM_ADDRESS, eeprom_buff, 2);

    eeprom_buff[0]=adc_offset & 0xff;
    eeprom_buff[1]=(adc_offset >> 8);
    eeprom_write_page(ADC_OFFSET_EEPROM_ADDRESS, eeprom_buff, 2);
}

void read_settings_from_eeprom() {
    uint8_t eeprom_buff[2];
    uint16_t res;

    eeprom_read_page(TANK_CAPACITY_EEPROM_ADDRESS, eeprom_buff, 2);
    res = eeprom_buff[1] << 8;
    res = res | eeprom_buff[0];
    set_tank_cap(res);

    eeprom_read_page(ADC_MULTIPLER_EEPROM_ADDRESS, eeprom_buff, 2);
    res = eeprom_buff[1] << 8;
    res = res | eeprom_buff[0];
    set_adc_multipl(res);

    eeprom_read_page(ADC_OFFSET_EEPROM_ADDRESS, eeprom_buff, 2);
    res = eeprom_buff[1] << 8;
    res = res | eeprom_buff[0];
    set_adc_offset(res);
}

void restore_default_settings() {
    tank_cap = DEFAULT_TANK_CAPACITY;
    adc_multipl = DEFAULT_ADC_MULTIPLER;
    adc_offset = DEFAULT_ADC_OFFSET;
    persist_settings_in_eeprom();
}