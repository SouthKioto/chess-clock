#include "buzzler.h"
#include "bitops.h"
#include "pin_conf.h"

typedef enum {
  T0_PRESCALER_1 = _BV(CS00),
  T0_PRESCALER_8 = _BV(CS01),
  T0_PRESCALER_64 = _BV(CS00) | _BV(CS01),
  T0_PRESCALER_256 = _BV(CS02),
  T0_PRESCALER_1024 = _BV(CS02) | _BV(CS00),
} Preskaler;

static void ustawPrescaler(Preskaler preskaler) { TCCR0B = preskaler; }

static unsigned short pobierzPreskaler(Preskaler preskaler) {
  unsigned short wspol;

  switch (preskaler) {
  case T0_PRESCALER_1:
    wspol = 1;
    break;

  case T0_PRESCALER_8:
    wspol = 8;
    break;
  case T0_PRESCALER_64:
    wspol = 64;
    break;
  case T0_PRESCALER_256:
    wspol = 256;
    break;
  case T0_PRESCALER_1024:
    wspol = 1024;
    break;
  }

  return wspol;
}

void buzzlerInit(void) {
  SET_BIT(BUZZLER_DDR, BUZZLER_PIN);
  CLR_BIT(BUZZLER_PORT, BUZZLER_PIN);
}

void buzzlerWlacz(void) {}

void buzzlerWylacz(void) {}
