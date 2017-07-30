#include "stm8s_gpio.h"
#include "utils.h"


// void set_led(bool state) {
//     LED_PORT->DDR |= LED_PIN;
// 	LED_PORT->CR1 |= LED_PIN;
//     if (state) {
//         LED_PORT->ODR &= ~LED_PIN;
//         return;
//     }
//     LED_PORT->ODR |= LED_PIN;
// }


void delay(uint32_t delay)
{
    int i, j;
    for(i=0; i<100 ;i++)
    {
       for(j=0; j<delay ;j++);
    }
}

// void led_blink(int32_t dur) {
//     set_led(TRUE);
//     delay(dur);
//     set_led(FALSE);
// }
