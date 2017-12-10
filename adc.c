#include "adc.h"
#include "stm8s_gpio.h"

void adc_init() {
    /* Clear the SPSEL bits */
    ADC1->CR1 &= (~ADC1_CR1_SPSEL);
    /* Select the prescaler division factor according to ADC1_PrescalerSelection values */
    ADC1->CR1 |= (ADC1_PRESSEL_FCPU_D2);
    /* Set the single conversion mode */
    ADC1->CR1 &= (~ADC1_CR1_CONT);
    /* Clear the ADC1 channels */
    ADC1->CSR &= (~ADC1_CSR_CH);
    /* Select the ADC1 channel */
    ADC1->CSR |= (ADC1_CHANNEL_5); // PD5
    /* The reading order should be MSB first and then LSB */
    ADC1->CR2 |= ADC1_ALIGN_LEFT;
    /* wakes up the ADC from power down mode */
    ADC1->CR1 |= ADC1_CR1_ADON;
}

uint16_t adc_read() {
    uint16_t temph = 0;
    uint8_t templ = 0;
    /* start conversion */
    ADC1->CR1 |= ADC1_CR1_ADON;
    
    /* Read LSB first */
    templ = ADC1->DRL;
    /* Then read MSB */
    temph = ADC1->DRH;

    return temph;
}