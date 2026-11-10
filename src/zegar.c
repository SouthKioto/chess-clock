#include "zegar.h"
#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/atomic.h>

volatile int32_t czas_teraz = 0;
volatile char czas_pauza = 0;

void zegarInit() {
    // ATmega328
    TCCR0A = BIT(WGM01);
    OCR0A = 249;
    TCCR0B = BIT(CS01) | BIT(CS00);
    TIMSK0 = BIT(OCIE0A);
    czas_pauza = 0;
}

void zegarPauza() {
    // TCCR0B pauza
    CLR_MASK(TCCR0B, BIT(CS02) | BIT(CS01) | BIT(CS00));
    czas_pauza = 1;
}

void zegarWznow() {
    // TCCR0B wznowienie dokladnie od momentu w ktorym zostal zatrzymany 
    SET_MASK(TCCR0B, BIT(CS01) | BIT(CS00));
    czas_pauza = 0;
}

char zegarCzyPauza() {
    return czas_pauza;
}

ISR(TIMER0_COMPA_vect) {
    czas_teraz++;
}

int32_t zegarMs() {
    int32_t ms_teraz;
    
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
        ms_teraz = czas_teraz;
    }
    
    return ms_teraz;
}