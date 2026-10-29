#include "../include/przyciski.h"
#include "bitops.h"
#include "pin_conf.h"
#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdint.h>

static volatile uint8_t zdarzenie = 0;

ISR(INT1_vect) {
  zdarzenie |= ZDARZENIE_GRACZ_1;
  CLR_BIT(EIMSK, INT1);
}

ISR(INT0_vect) {
  zdarzenie |= ZDARZENIE_GRACZ_2;
  CLR_BIT(EIMSK, INT0);
}

ISR(PCINT2_vect) {
  if (IS_CLR(BTN3_PIN, BTN3_BIT) && IS_SET(PCMSK2, PCINT20)) {
    zdarzenie |= ZDARZENIE_START;
    CLR_BIT(PCMSK2, PCINT20);
  }

  if (IS_CLR(BTN4_PIN, BTN4_BIT) && IS_SET(PCMSK2, PCINT21)) {
    zdarzenie |= ZDARZENIE_PODDANIE;
    CLR_BIT(PCMSK2, PCINT21);
  }
}

void przyciskiInit(void) {
  // conf buttonow
  CLR_BIT(BTN1_DDR, BTN1_BIT);
  SET_BIT(BTN1_PORT, BTN1_BIT);

  CLR_BIT(BTN2_DDR, BTN2_BIT);
  SET_BIT(BTN2_PORT, BTN2_BIT);

  CLR_BIT(BTN3_DDR, BTN3_BIT);
  SET_BIT(BTN3_PORT, BTN3_BIT);

  CLR_BIT(BTN4_DDR, BTN4_BIT);
  SET_BIT(BTN4_PORT, BTN4_BIT);

  // reakcja na zbocze opadajace
  SET_BIT(EICRA, ISC01);
  SET_BIT(EICRA, ISC11);

  // kasowanie smieci
  SET_BIT(EIFR, INTF0);
  SET_BIT(EIFR, INTF1);

  // wlaczenie przerwania
  SET_BIT(EIMSK, INT0);
  SET_BIT(EIMSK, INT1);

  SET_BIT(PCMSK2, PCINT20);
  SET_BIT(PCMSK2, PCINT21);

  SET_BIT(PCIFR, PCIF2);
  SET_BIT(PCICR, PCIE2);
}

uint8_t przyciskiPobierzZdarzenia(void) {
  // wylaczam przerwanie
  cli();
  uint8_t zdarzenie_tmp = zdarzenie;
  zdarzenie = 0;
  sei();
  return zdarzenie_tmp;
}

void przyciskiReset(void) {
  if (IS_CLR(EIMSK, INT1) && IS_SET(BTN1_PIN, BTN1_BIT)) {
    SET_BIT(EIFR, INTF1);
    SET_BIT(EIMSK, INT1);
  }
  if (IS_CLR(EIMSK, INT0) && IS_SET(BTN2_PIN, BTN2_BIT)) {
    SET_BIT(EIFR, INTF0);
    SET_BIT(EIMSK, INT0);
  }
  if (IS_CLR(PCMSK2, PCINT20) && IS_SET(BTN3_PIN, BTN3_BIT)) {
    SET_BIT(PCIFR, PCIF2);
    SET_BIT(PCMSK2, PCINT20);
  }
  if (IS_CLR(PCMSK2, PCINT21) && IS_SET(BTN4_PIN, BTN4_BIT)) {
    SET_BIT(PCIFR, PCIF2);
    SET_BIT(PCMSK2, PCINT21);
  }
}
