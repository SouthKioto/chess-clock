#include "czas_gracza.h"

#define MS_NA_MIN 60000L

#define MAX_CZAS 90
#define MIN_CZAS 1
#define DEFAULT_CZAS 5

static uint16_t ustawioneMinuty = DEFAULT_CZAS;

bool czasUstaw(uint16_t minuty) {

  if (minuty >= MIN_CZAS && minuty <= MAX_CZAS) {
    ustawioneMinuty = minuty;
    return true;
  } else {
    return false;
  }
}
uint16_t czasPobierzUstawiony(void) { return ustawioneMinuty; }
