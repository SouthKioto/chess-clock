#include "../include/bitops.h"
#include "../include/pin_conf.h"
#include <util/delay.h>

int main(void) {
  SET_BIT(LED_DDR, LED_PIN);

  while (1) {
    TOGGLE_BIT(LED_PORT, LED_PIN);
    _delay_ms(500);
  }

  return 0;
}
