#include <libopencm3/cm3/common.h> // ← REQUIRED
#include <libopencm3/stm32/f0/rcc.h>
#include <libopencm3/stm32/gpio.h>

/* Vector Table / Startup for STM32F072RB */
extern uint32_t _estack; // Defined in linker script

void Reset_Handler(void);
int main(void);

// The Vector Table
__attribute__((section(".isr_vector")))
uint32_t *vector_table[] = {
    (uint32_t *)&_estack,
    (uint32_t *)Reset_Handler};

void Reset_Handler(void)
{
    // Basic initialization could go here (copying .data, zeroing .bss)
    // For a simple blinky, calling main is usually enough
    main();
    while (1)
        ;
}

#define LED_PORT (GPIOA)
#define LED_PIN (GPIO5)

static void rcc_setup(void)
{
    rcc_clock_setup_in_hsi_out_48mhz();
}

static void gpio_setup(void)
{
    rcc_periph_clock_enable(RCC_GPIOA);
    gpio_mode_setup(LED_PORT, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, LED_PIN);
}

static void delay_cycles(uint32_t cycles)
{
    for (uint32_t i = 0; i < cycles; i++)
        __asm__("nop");
}

int main(void)
{
    rcc_setup();
    gpio_setup();

    while (1)
    {
        gpio_toggle(LED_PORT, LED_PIN);
        delay_cycles(48000000 / 4);
    }
}
