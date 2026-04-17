#ifndef INC_SYSTEM_H
#define INC_SYSTEM_H

#include "common-defines.h"

#define CPU_FREQUNCY (48000000)
#define SYSTICK_FREQUNCY (1000)


void system_setup(void);      //systick_setup changes to this...
uint64_t system_get_ticks(void);

#endif