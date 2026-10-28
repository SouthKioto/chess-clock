#include "../include/bitops.h"
#include "../include/pin_conf.h"
#include "../include/przyciski.h"

#include <stdio.h>
#include <util/delay.h>

int main(void) {

  while (1) {
    przyciskiInit();
  }

  return 0;
}
