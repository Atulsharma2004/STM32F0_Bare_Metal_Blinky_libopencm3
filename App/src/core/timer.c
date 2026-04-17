#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/timer.h>
#include <libopencm3/stm32/f0/rcc.h>
#include <libopencm3/stm32/f0/timer.h>
#include <libopencm3/stm32/f0/memorymap.h>
#include "core/timer.h"

// Freq: 84,000,000
//  freq = system_freq / ((prescaler - 1) + (arr - 1))

#define PRESCALER (48)
#define ARR_VALUE (1000)


void timer_setup(void)
{
    rcc_periph_clock_enable(RCC_TIM2);
    rcc_periph_reset_pulse(RST_TIM2);

    timer_set_prescaler(TIM2, PRESCALER - 1);
    timer_set_period(TIM2, ARR_VALUE - 1);

    // Explicitly set direction and alignment
    timer_set_mode(TIM2, TIM_CR1_CKD_CK_INT, TIM_CR1_CMS_EDGE, TIM_CR1_DIR_UP);

    timer_set_oc_mode(TIM2, TIM_OC1, TIM_OCM_PWM1);
    timer_enable_oc_preload(TIM2, TIM_OC1);
    timer_enable_preload(TIM2);
    timer_set_oc_polarity_high(TIM2, TIM_OC1); // Ensure polarity is active high
    timer_enable_oc_output(TIM2, TIM_OC1);

    timer_enable_break_main_output(TIM2); // Not needed for TIM2 on F0

    timer_set_oc_value(TIM2, TIM_OC1, 500);
    timer_enable_counter(TIM2);
}

void timer_pwm_set_duty_cycle(uint32_t duty)
{
    if (duty > 100)
        duty = 100;

    uint32_t ccr = (ARR_VALUE * duty) / 100;
    timer_set_oc_value(TIM2, TIM_OC1, ccr);
}

// void timer_pwm_set_duty_cycle(float duty_cycle){
//     // duty_cycle = (ccr / arr) * 100;
//     //ccr = (duty_cycle / 100) * arr;

//     const float raw_value = (float)ARR_VALUE * (duty_cycle / 100.0f);
//     timer_set_oc_value(TIM2, TIM_OC1, (uint32_t)raw_value);

// }