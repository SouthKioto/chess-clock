#include "buzzler.h"
#include "bitops.h"
#include "pin_conf.h"

void buzzlerInit(void) {
  SET_BIT(BUZZLER_DDR, BUZZLER_PIN);
  CLR_BIT(BUZZLER_PORT, BUZZLER_PIN);

  TCCR1A = 0;
  SET_BIT(TCCR1B, WGM12);
}

void buzzlerWlacz(uint16_t freq) {
  OCR1A = (F_CPU / (2UL * 8 * freq)) - 1;
  OCR1B = 0;
}

void buzzlerWylacz(void) {}
