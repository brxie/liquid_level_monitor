
#define LED_PORT        (GPIOB)
#define LED_PIN         (GPIO_PIN_5)

void set_led(bool state);

void delay(uint32_t delay);

void led_blink(int32_t dur);