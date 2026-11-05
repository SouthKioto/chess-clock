#include "../include/timer.h"
#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/atomic.h>

volatile unsigned __int32 czas_teraz = 0;

// ATmega328 
// TODO abstract layer
void cTimerInit() {
    TCCR0A = (1 << WGM01);
    OCR0A = 249;
    TCCR0B = (1 << CS01) | (1 << CS00);
    TIMSK0 = (1 << OCIE0A);
}

ISR(TIMER0_COMPA_vect) {
    czas_teraz++;
}

__int32 cTimerMs() {
    __int32 ms_tera;
    
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
        ms_tera = czas_teraz;
    }
    
    return ms_tera;
}