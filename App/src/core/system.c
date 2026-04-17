#include <libopencm3/cm3/systick.h>
#include <libopencm3/stm32/f0/rcc.h>
#include "core/system.h"



static volatile uint64_t ticks = 0;


void sys_tick_handler(void)
{
    ticks++;
}


static void rcc_setup(void)
{
    rcc_clock_setup_in_hsi_out_48mhz();

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


uint64_t system_get_ticks(void)
{
    return ticks;
}

void system_setup(void){
    rcc_setup();
    systick_setup();
}
