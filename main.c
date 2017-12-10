#include "stm8s.h"
#include "stm8s_beep.h"
#include "stm8s_clk.h"
#include "stm8s_gpio.h"
#include "stm8s_tim4.h"
#include "stm8s_tim2.h"

#include <utils.h>

#include "eeprom.h"
#include "pcd8544.h"
#include "view.h"
#include "stats.h"

#define BUTTONS_PORT GPIOA
#define BUTTON_MENU_PIN GPIO_PIN_1
#define BUTTON_OK_PIN GPIO_PIN_2
#define MAIN_MENU_REFRESH_FREQ 15

typedef enum {MAIN_MENU, STATISTICS, SETTINGS} Menu;
Menu menu = MAIN_MENU;

uint8_t butns_cnt[7] = {0};
uint8_t butns_press_flag = 0;
extern uint8_t sett_cusr_pos;
uint8_t last_menu;
uint8_t main_menu_refresh_cnt = 0;

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
    /* Input with pull-up */
    BUTTONS_PORT->DDR &= ~(BUTTON_MENU_PIN | BUTTON_OK_PIN);
    BUTTONS_PORT->CR1 |= (BUTTON_MENU_PIN | BUTTON_OK_PIN);
}

static void TIM2_Config(void) 
{ 
    //CLK_PeripheralClockConfig(CLK_PERIPHERAL_TIMER2, ENABLE); 
    CLK->PCKENR1 |= (1 << (CLK_PERIPHERAL_TIMER2 & 0x0F));

    // TIM2->CR1 = TIM2_CR1_RESET_VALUE;
    // TIM2->IER = TIM2_IER_RESET_VALUE;
    // TIM2->PSCR = TIM2_PSCR_RESET_VALUE;
    // TIM2->SR1 = TIM2_SR1_RESET_VALUE;

    TIM2->PSCR = (uint8_t)TIM2_PRESCALER_32;
    /* Set the Autoreload value */
    TIM2->ARRL = (0x00);
    TIM2->ARRH = (0xFF);

    //TIM2_ITConfig(TIM2_IT_UPDATE, ENABLE); 
    TIM2->IER |= ENABLE;
    //TIM2_Cmd(ENABLE);
    TIM2->CR1 |= TIM2_CR1_CEN;
} 

static void TIM4_Config(void) 
{ 
    //CLK_PeripheralClockConfig(CLK_PERIPHERAL_TIMER4, ENABLE); 
    CLK->PCKENR1 |= (1 << (CLK_PERIPHERAL_TIMER4 & 0x0F));

    // TIM4->CR1 = TIM4_CR1_RESET_VALUE;
    // TIM4->IER = TIM4_IER_RESET_VALUE;
    // TIM4->CNTR = TIM4_CNTR_RESET_VALUE;
    // TIM4->PSCR = TIM4_PSCR_RESET_VALUE;
    // TIM4->ARR = TIM4_ARR_RESET_VALUE;
    // TIM4->SR1 = TIM4_SR1_RESET_VALUE;

    TIM4->PSCR = (TIM4_PRESCALER_128);
    /* Set the Autoreload value */
    TIM4->ARR = (0xFF);

    //TIM4_ITConfig(TIM4_IT_UPDATE, ENABLE); 
    TIM4->IER |= TIM4_IT_UPDATE;
    //TIM4_Cmd(ENABLE);    // Enable TIM4  
    TIM4->CR1 |= TIM4_CR1_CEN;
}

void beep_init() {
  /* Set a default calibration value if no calibration is done */
  if ((BEEP->CSR & BEEP_CSR_BEEPDIV) == BEEP_CSR_BEEPDIV)
  {
    BEEP->CSR &= (uint8_t)(~BEEP_CSR_BEEPDIV); /* Clear bits */
    BEEP->CSR |= BEEP_CALIBRATION_DEFAULT;
  }
  
  /* Select the output frequency */
  BEEP->CSR &= (uint8_t)(~BEEP_CSR_BEEPSEL);
  BEEP->CSR |= (uint8_t)(BEEP_FREQUENCY_2KHZ);

}

void beep(uint16_t duration) {
    BEEP->CSR |= BEEP_CSR_BEEPEN;
    delay(duration);
    BEEP->CSR &= ~BEEP_CSR_BEEPEN;
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
    return !buttonReleased(gpio_port, gpio_pin);
}

/* Returns state of button:
    0 - non active
    1 - clicled button
    2 - continuous button
*/
uint8_t getButtonState(GPIO_TypeDef* gpio_port, uint8_t gpio_pin) {
    if (buttonReleased(gpio_port, gpio_pin)) {
        butns_press_flag &= ~(1 << gpio_pin);
    } else {
        if (butns_cnt[gpio_pin] < 0xFF) {
            butns_cnt[gpio_pin]++;
        }
    }
    if (!(butns_press_flag >> gpio_pin) & 1) {
        /* continuous button */
        if (butns_cnt[gpio_pin]>200) {
            if (buttonReleased(gpio_port, gpio_pin)) {
                butns_press_flag |= 1 << gpio_pin;
                butns_cnt[gpio_pin] = 0;
                beep(800);
                return 2;
            }
        }
        /* normal button */
        if (butns_cnt[gpio_pin]>2) {
            if (buttonReleased(gpio_port, gpio_pin)) {
                butns_cnt[gpio_pin] = 0;
                beep(400);
                return 1;
            }
        }
    }
    return 0;
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

    beep_init();
    
    /* stats */
    init_stats();

    read_settings_from_eeprom();
    if(buttonPressed(BUTTONS_PORT, BUTTON_OK_PIN)) {
        restore_default_settings();
        print_info("REST SETT");
    }

    enableInterrupts();
    
    while (1)
    {
    }
}

/* LCD timer2 handler */
INTERRUPT_HANDLER(TIM2_UPD_OVF_IRQHandler, 13) 
{   
    switch(menu) {
    case MAIN_MENU:
        if (menu != last_menu) {
            pcd8544_cls_soft();
        }
        if (main_menu_refresh_cnt == 0) {
            render_main_menu(get_percent_fill(), get_space_used(), get_space_left());
            main_menu_refresh_cnt = MAIN_MENU_REFRESH_FREQ;
        }
        main_menu_refresh_cnt--;
        break;
    case STATISTICS:
        if (menu != last_menu) {
            pcd8544_cls_soft();
        }
        render_stats();
        main_menu_refresh_cnt = 0;
        break;
    
    case SETTINGS:
        if (menu != last_menu) {
            pcd8544_cls();
        }
        render_settings();
        main_menu_refresh_cnt = 0;
        break;
    }
  
    last_menu = menu;
    TIM2->SR1 = (~TIM2_IT_UPDATE);
}

/* buttons timer4 handling timer */
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
        buttonState = getButtonState(BUTTONS_PORT, BUTTON_MENU_PIN);
        if (buttonState == 2) {
            sett_cusr_pos++;
        }
        if (buttonState == 1) {
            menu = MAIN_MENU;
            persist_settings_in_eeprom();
        }

        buttonState = getButtonState(BUTTONS_PORT, BUTTON_OK_PIN);
        if (buttonState == 2) {
            toggle_sett_step_mode();
        }
        if (buttonState == 1) {
            step_activ_sett_val();
        }
        
        break;
    }

    TIM4->SR1 = (~TIM4_IT_UPDATE);
}
