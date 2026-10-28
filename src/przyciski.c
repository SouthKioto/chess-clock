#include "../include/przyciski.h"
#include "bitops.h"
#include "pin_conf.h"
#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdint.h>

/*
  L.yellow    - rund. gr. 1
  L.orange    - rund. gr. 2
  L.czerwona  - START/PAUZA
  L.white     - PODDANIE

  przypadek testowy:
  1. przycisniecie start (gasnie l.red)
  2. runda gracza 1 (swieci L.yellow)
  3. przyciska gracz 1 (zmiana na L.orange)
  4. przyciska gracz 2 (zmana na l.yellow)
  5. przyciska pauza (zaswieca sie l.red)
  6. przyciska pauza (gasnie l.red)
  7. przyciska poddanie (zaswieca sie l.white -> reset wszystkiego)

 */

static volatile uint8_t zdarzenie = 0;

ISR(INT0_vect) { zdarzenie |= ZDARZENIE_GRACZ_1; }

ISR(PCINT2_vect) {
  if (READ_BIT(PIND, PD4)) {
    zdarzenie |= ZDARZENIE_GRACZ_2;
  }
}

void przyciskiInit(void) {
  CLR_BIT(BTN1_DDR, BTN1_BIT);
  SET_BIT(BTN1_PORT, BTN1_BIT);

  CLR_BIT(BTN2_DDR, BTN2_BIT);
  SET_BIT(BTN2_PORT, BTN2_BIT);

  CLR_BIT(BTN3_DDR, BTN3_BIT);
  SET_BIT(BTN3_PORT, BTN3_BIT);

  CLR_BIT(BTN4_DDR, BTN4_BIT);
  SET_BIT(BTN4_PORT, BTN4_BIT);
}

void przyciskiReset(void) {}
