// STM32 NUCLEO-F072RB

#include <libopencm3/cm3/common.h> // ← REQUIRED
#include <libopencm3/stm32/f0/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/cm3/systick.h>
// #include <libopencm3/cm3/scb.h>

#define LED_PORT (GPIOA)
#define LED_PIN (GPIO5)

#define CPU_FREQUNCY (48000000)
#define SYSTICK_FREQUNCY (1000)

volatile uint64_t ticks = 0;
// void __attribute__((used)) sys_tick_handler(void)
// {
//     ticks++;
// }
void sys_tick_handler(void)
{
    ticks++;
}

static uint64_t get_ticks(void)
{
    return ticks;
}

static void rcc_setup(void)
{
    rcc_clock_setup_in_hsi_out_48mhz();
    // rcc_clock_setup_pll(&rcc_hsi_configs[RCC_CLOCK_HSI_48MHZ])
}

static void gpio_setup(void)
{
    rcc_periph_clock_enable(RCC_GPIOA);
    gpio_mode_setup(LED_PORT, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, LED_PIN);
}

static void systick_setup(void)
{
    /* SysTick reload = CPU_FREQ / tick_rate - 1 */
    systick_set_reload(CPU_FREQUNCY / SYSTICK_FREQUNCY - 1);

    /* Use core clock */
    systick_set_clocksource(STK_CSR_CLKSOURCE_AHB);

    /* Clear current value */
    systick_clear();

    /* Enable interrupt + counter */
    systick_interrupt_enable();
    systick_counter_enable();
}

int main(void)
{
    rcc_setup();
    gpio_setup();
    systick_setup();

    uint64_t start_time = get_ticks();
    while (1)
    {
        if ((get_ticks() - start_time) >= 1000)
        {
            gpio_toggle(LED_PORT, LED_PIN);
            start_time = get_ticks();
        }
        // Do some useful work
    }
}
