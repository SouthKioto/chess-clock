#include "czas_gracza.h"
#include "zegar.h"

#define MS_NA_MIN 60000L

#define MAX_CZAS 90
#define MIN_CZAS 1
#define DEFAULT_CZAS 5

static uint16_t ustawioneMinuty = DEFAULT_CZAS;
static int32_t pozostalo[2];
static Gracze aktywny;
static int32_t ostatniOdczyt;

bool czasUstaw(uint16_t minuty) {

  if (minuty >= MIN_CZAS && minuty <= MAX_CZAS) {
    ustawioneMinuty = minuty;
    return true;
  } else {
    return false;
  }
}

uint16_t czasPobierzUstawiony(void) { return ustawioneMinuty; }

void czasStart(void) {
  pozostalo[GRACZ_1] = pozostalo[GRACZ_2] =
      (int32_t)ustawioneMinuty * MS_NA_MIN;
  aktywny = GRACZ_1;
  ostatniOdczyt = zegarMs();
}

void czasAktualizuj(void) {
  int32_t teraz = zegarMs();
  int32_t minelo = teraz - ostatniOdczyt;
  ostatniOdczyt = teraz;

  pozostalo[aktywny] -= minelo;

  if (pozostalo[aktywny] < 0) {
    pozostalo[aktywny] = 0;
  }
}

void czasPrzelacz(Gracze gracz) {
  czasAktualizuj();
  aktywny = gracz;
}

Gracze czasAktywny(void) { return aktywny; }

int32_t czasPobierz(Gracze gracz) { return (int32_t)pozostalo[gracz]; }

bool czasKoniec(void) {
  if ((int32_t)pozostalo[GRACZ_1] <= 0 || (int32_t)pozostalo[GRACZ_2] <= 0) {
    // koniec czasu
    return true;
  }
  return false;
}
