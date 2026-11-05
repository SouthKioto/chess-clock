#ifndef TIMER_H
#define TIMER_H
#include <stdint.h>

// MSVC type -> GCC (avr spec) type
#ifndef __int32
#define __int32 int32_t
#endif

void cTimerInit();

__int32 cTimerMs();

#endif