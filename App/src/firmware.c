// STM32 NUCLEO-F072RB

#include <libopencm3/cm3/common.h> // ← REQUIRED
#include <libopencm3/stm32/f0/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <core/system.h>
#include <core/timer.h>

// #include <libopencm3/cm3/scb.h>

#define LED_PORT (GPIOA)
#define LED_PIN (GPIO5)

// GPIO_Toggling
//  static void gpio_setup(void)
//  {
//      rcc_periph_clock_enable(RCC_GPIOA);
//      gpio_mode_setup(LED_PORT, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, LED_PIN);
//  }

// PWM Setup
static void gpio_setup(void)
{
    rcc_periph_clock_enable(RCC_GPIOA);
    gpio_mode_setup(LED_PORT, GPIO_MODE_AF, GPIO_PUPD_NONE, LED_PIN);
    gpio_set_af(LED_PORT, GPIO_AF2, LED_PIN); // AF2 is TIM2_CH1 on PA5
}

int main(void)
{
    system_setup();
    gpio_setup();
    timer_setup();

    // If LED is ON now, the hardware/clock is fine.
    // Now wait a bit so you can see it before PWM takes over.
    for (volatile int i = 0; i < 100000; i++)
        ;

    uint64_t start_time = system_get_ticks();
    uint32_t duty = 0;
    int8_t step = 1;

    // timer_pwm_set_duty_cycle(duty_cycle);
    while (1)
    {
        // Do some useful work
        if ((system_get_ticks() - start_time) >= 1000)  // Update every 10ms
        {
            // Ping-pong fading logic
            if (duty >= 100 && step > 0)
                step = -1;
            else if (duty == 0 && step < 0)
                step = 1;

            duty += step;

            timer_pwm_set_duty_cycle(duty);
            start_time = system_get_ticks();
        }
    }
}
