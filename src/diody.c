#include "diody.h"
#include "bitops.h"
#include "pin_conf.h"

void diodyInit(void) {
  SET_BIT(LED1_DDR, LED1_PIN);
  CLR_BIT(LED1_PORT, LED1_PIN);

  SET_BIT(LED2_DDR, LED2_PIN);
  CLR_BIT(LED2_PORT, LED2_PIN);

  SET_BIT(LED3_DDR, LED3_PIN);
  SET_BIT(LED3_PORT, LED3_PIN);

  SET_BIT(LED4_DDR, LED4_PIN);
  CLR_BIT(LED4_PORT, LED4_PIN);
}
