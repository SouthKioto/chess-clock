#include "../include/zegar.h"
#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/atomic.h>

volatile unsigned __int32 czas_teraz = 0;

void zegarInit() {
    // ATmega328
    TCCR0A = BIT(WGM01);
    OCR0A = 249;
    TCCR0B = BIT(CS01) | BIT(CS00);
    TIMSK0 = BIT(OCIE0A);
}

ISR(TIMER0_COMPA_vect) {
    czas_teraz++;
}

__int32 zegarMs() {
    __int32 ms_teraz;
    
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
        ms_teraz = czas_teraz;
    }
    
    return ms_teraz;
}