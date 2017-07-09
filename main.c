#include "stm8s.h"
#include "stm8s_adc1.h"
#include "stm8s_clk.h"
#include "stm8s_exti.h"
#include "stm8s_gpio.h"
#include "stm8s_tim4.h"
#include "stm8s_tim2.h"


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <utils.h>

#include "pcd8544.h"
#include "view.h"
#include "stats.h"

#define BUTTONS_PORT GPIOA
#define BUTTON_MENU_PIN GPIO_PIN_1
#define BUTTON_OK_PIN GPIO_PIN_2


typedef enum {MAIN_MENU, STATISTICS, SETTINGS} Menu;
Menu menu = MAIN_MENU;
uint16_t count = 0;
uint16_t tim2_tempo = 0;
uint16_t butn_cnt = 0;
uint8_t butn_press_flag = 0;

/* Setup the system clock to run at 16MHz using the internal oscillator. */
void CLK_Config()
{
    CLK->ICKR = 0;                       //  Reset the Internal Clock Register.
    CLK->ICKR = CLK_ICKR_HSIEN;                //  Enable the HSI.
    CLK->ECKR = 0;                       //  Disable the external clock.
    while ((CLK->ICKR & CLK_ICKR_HSIRDY) == 0); // Wait for the HSI to be ready for use.
    CLK->CKDIVR = 0;                     //  Ensure the clocks are running at full speed.
    CLK->PCKENR1 = 0xff;                 //  Enable all peripheral clocks.
    CLK->PCKENR2 = 0xff;                 //  Ditto.
    CLK->CCOR &= (~CLK_CCOR_CCOEN);      //  Turn off CCO.
    CLK->HSITRIMR = 0;                   //  Turn off any HSIU trimming.
    CLK->SWIMCCR = 0;                    //  Set SWIM to run at clock / 2.
    CLK->SWR = 0xe1;                     //  Use HSI as the clock source.
    CLK->SWCR = 0;                       //  Reset the clock switch control register.
    CLK->SWCR |= CLK_SWCR_SWEN;                 //  Enable switching.
    while ((CLK->SWCR & CLK_SWCR_SWBSY) != 0 );        //  Pause while the clock switch is busy.
}


static void GPIO_Config(void)
{
    BUTTONS_PORT->DDR &= ~BUTTON_MENU_PIN;
    /* Input with pull-up */
    BUTTONS_PORT->CR1 |= BUTTON_MENU_PIN;
    // /* External interrupt disabled */
    // BUTTONS_PORT->CR2 |= BUTTON_MENU_PIN;
}

static void TIM2_Config(void) 
{ 
    //CLK_PeripheralClockConfig(CLK_PERIPHERAL_TIMER2, ENABLE); 
    CLK->PCKENR1 |= (1 << (CLK_PERIPHERAL_TIMER2 & 0x0F));

    //TIM4_DeInit(); 
    TIM2->CR1 = TIM2_CR1_RESET_VALUE;
    TIM2->IER = TIM2_IER_RESET_VALUE;
    TIM2->PSCR = TIM2_PSCR_RESET_VALUE;
    TIM2->SR1 = TIM2_SR1_RESET_VALUE;

    TIM2->PSCR = (uint8_t)TIM2_PRESCALER_2;
    /* Set the Autoreload value */
    TIM2->ARRL = (0x00);
    TIM2->ARRH = (0xFF);

    //TIM2_ITConfig(TIM2_IT_UPDATE, ENABLE); 
    TIM2->IER |= ENABLE;
    //TIM2_Cmd(ENABLE);    // Enable TIM2  
    TIM2->CR1 |= TIM2_CR1_CEN;
} 

static void TIM4_Config(void) 
{ 
  //CLK_PeripheralClockConfig(CLK_PERIPHERAL_TIMER4, ENABLE); 
  CLK->PCKENR1 |= (1 << (CLK_PERIPHERAL_TIMER4 & 0x0F));
  
  //TIM4_DeInit(); 
  TIM4->CR1 = TIM4_CR1_RESET_VALUE;
  TIM4->IER = TIM4_IER_RESET_VALUE;
  TIM4->CNTR = TIM4_CNTR_RESET_VALUE;
  TIM4->PSCR = TIM4_PSCR_RESET_VALUE;
  TIM4->ARR = TIM4_ARR_RESET_VALUE;
  TIM4->SR1 = TIM4_SR1_RESET_VALUE;

  TIM4->PSCR = (TIM4_PRESCALER_128);
  /* Set the Autoreload value */
  TIM4->ARR = (0xFF);

  //TIM4_ITConfig(TIM4_IT_UPDATE, ENABLE); 
  TIM4->IER |= TIM4_IT_UPDATE;
  //TIM4_Cmd(ENABLE);    // Enable TIM4  
  TIM4->CR1 |= TIM4_CR1_CEN;
} 


static void EXTI_Config(void)
{
    EXTI->CR1 &= (~EXTI_CR1_PAIS);
    EXTI->CR1 |= (EXTI_SENSITIVITY_FALL_LOW);
    EXTI->CR2 &= (~EXTI_CR2_TLIS);
    EXTI->CR2 |= (EXTI_SENSITIVITY_FALL_LOW);
}


main()
{
    disableInterrupts();
    CLK_Config();
	

    GPIO_Config();
    TIM4_Config();
    TIM2_Config();

    /* lcd init */
	pcd8544_init();

    /* lcd view */
    draw_layout();
    draw_level(35);
    draw_percent(35);
    draw_stats(0, 0);

    /* stats */
    init_stats();
    set_adc_min(335);
    set_adc_max(394);

    ITC->ISPR1 = 0x00;
    ITC->ISPR4 = 0;
    ITC->ISPR4 |= (0x03<<2);

    enableInterrupts();
    
    while (1)
    {

    }
}

/* LCD timer2 handler */
uint8_t last_menu;
INTERRUPT_HANDLER(TIM2_UPD_OVF_IRQHandler, 13) 
{ 
    uint16_t liquid_level;
    
    switch(menu) {
    case MAIN_MENU:
        if (menu != last_menu) {
            pcd8544_cls_soft();
        }
        if (tim2_tempo>1) 
        { 
            draw_layout();
            liquid_level = get_liquid_level();
            draw_stats(butn_cnt, butn_press_flag);
            draw_percent(liquid_level);
            draw_level(liquid_level);
            tim2_tempo = 0;
        }
    case STATISTICS:
        if (menu != last_menu) {
            pcd8544_cls_soft();
        }
         if (tim2_tempo>10) {
            pcd8544_rect(0,0,84,48,1);
            set_curr_pos(1, 0);
            pcd8544_print("Statistics:");
            pcd8544_refresh();
            tim2_tempo = 0;
        }
    
    case SETTINGS:
        if (menu != last_menu) {
            pcd8544_cls();
        }
        if (tim2_tempo>10) {
            pcd8544_rect(0,0,84,48,1);
            set_curr_pos(1, 0);
            pcd8544_print("Settings:");
            pcd8544_refresh();
            tim2_tempo = 0;
        }
    }
  
    last_menu = menu;

    tim2_tempo++; 
    TIM2->SR1 = (~TIM2_IT_UPDATE);
}


uint8_t buttonReleased(GPIO_TypeDef* gpio_port, uint8_t gpio_pin) {
    
    if (gpio_port->IDR & gpio_pin) {
        delay(30);
        if (gpio_port->IDR & gpio_pin) {
            return 1;
        }
    }
    return 0;
}

uint8_t buttonPressed(GPIO_TypeDef* gpio_port, uint8_t gpio_pin) {
    delay(200);
    return !buttonReleased(gpio_port, gpio_pin);
}

/* Returns state of button:
    0 - non active
    1 - clicled button
    2 - continuous button
*/
uint8_t getButtonState(GPIO_TypeDef* gpio_port, uint8_t gpio_pin) {
    if (buttonReleased(gpio_port, gpio_pin)) {
        butn_press_flag = 0;  
    } else {
        butn_cnt++;
    }
    if (!butn_press_flag) {
        /* continuous button */
        if (butn_cnt>50) {
            if (buttonReleased(gpio_port, gpio_pin)) {
                butn_press_flag = 1;
                butn_cnt = 0;
                return 2;
            }
        }
        /* normal button */
        if (butn_cnt>3) {
            if (buttonReleased(gpio_port, gpio_pin)) {
                butn_cnt = 0;
                return 1;
            }
        }
    }
    return 0;
}

/* buttons handling timer */
INTERRUPT_HANDLER(TIM4_UPD_OVF_IRQHandler, 23) 
{ 
    int8_t buttonState = 0;
    switch(menu)
    {
    case MAIN_MENU:
        buttonState = getButtonState(BUTTONS_PORT, BUTTON_MENU_PIN);
        if (buttonState == 1) {
            menu++;
            if (menu > STATISTICS) {
                menu = MAIN_MENU;
            }
        }
        if (buttonState == 2) {
            menu = SETTINGS;
        }
        break;
    case STATISTICS:
        if (getButtonState(BUTTONS_PORT, BUTTON_MENU_PIN)) {
            menu = MAIN_MENU;
        }
        break;

    case SETTINGS:
        if (getButtonState(BUTTONS_PORT, BUTTON_MENU_PIN)) {
            menu = MAIN_MENU;
        }
        break;
    default:
        led_blink(10);
        if (getButtonState(BUTTONS_PORT, BUTTON_MENU_PIN)) {
            menu = MAIN_MENU;
        }
        break;
    }

    TIM4->SR1 = (~TIM4_IT_UPDATE);
}
