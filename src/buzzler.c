#include "buzzler.h"
#include "bitops.h"
#include "pin_conf.h"

#define BUZZ_PRESKALER 8UL
#define BUZZ_ZEGAR_TIMERA (F_CPU / BUZZ_PRESKALER)
#define BUZZ_PRESKALER_BITY _BV(CS11)

#define BUZZ_MIN_HZ ((BUZZ_ZEGAR_TIMERA / 2UL / 65536UL) + 1UL)

static uint16_t aktualneHz;

static uint16_t obliczTop(uint16_t hz) {
  uint32_t dzielnik = 2UL * hz;
  return (uint16_t)(((BUZZ_ZEGAR_TIMERA + dzielnik / 2UL) / dzielnik) - 1UL);
}

void buzzlerInit(void) {
  SET_BIT(BUZZLER_DDR, BUZZLER_PIN);
  CLR_BIT(BUZZLER_PORT, BUZZLER_PIN);

  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1 = 0;
  OCR1B = 0;

  aktualneHz = 0;
}

void buzzlerWlacz(uint16_t hz) {
  if (hz < BUZZ_MIN_HZ) {
    buzzlerWylacz();
    return;
  }

  if (hz == aktualneHz) {
    return;
  }

  TCCR1B = 0;
  OCR1A = obliczTop(hz);
  TCNT1 = 0;

  TCCR1A = _BV(COM1B0);
  TCCR1B = _BV(WGM12) | BUZZ_PRESKALER_BITY;

  aktualneHz = hz;
}

void buzzlerWylacz(void) {
  TCCR1B = 0;
  TCCR1A = 0;
  CLR_BIT(BUZZLER_PORT, BUZZLER_PIN);

  aktualneHz = 0;
}
