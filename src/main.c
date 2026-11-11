#include "bitops.h"
#include "buzzler.h"
#include "czas_gracza.h"
#include "diody.h"
#include "pin_conf.h"
#include "przyciski.h"
#include "zegar.h"

#include <avr/interrupt.h>
#include <util/delay.h>

typedef enum { USTAWIANIE, STOP, RUCH_GR_1, RUCH_GR_2, PODDANIE } Stan;

static void pokazStan(Stan stan) {
  CLR_BIT(LED1_PORT, LED1_PIN);
  CLR_BIT(LED2_PORT, LED2_PIN);
  CLR_BIT(LED3_PORT, LED3_PIN);
  CLR_BIT(LED4_PORT, LED4_PIN);

  switch (stan) {
  case USTAWIANIE:
    SET_BIT(LED4_PORT, LED4_PIN);
    SET_BIT(LED3_PORT, LED3_PIN);

    break;
  case STOP:
    SET_BIT(LED3_PORT, LED3_PIN);
    break;

  case RUCH_GR_1:
    SET_BIT(LED1_PORT, LED1_PIN);
    break;

  case RUCH_GR_2:
    SET_BIT(LED2_PORT, LED2_PIN);
    break;

  case PODDANIE:
    SET_BIT(LED4_PORT, LED4_PIN);
    break;
  }
}

static void pokazPoddanie(void) {
  pokazStan(PODDANIE);

  buzzlerWlacz(800);
  _delay_ms(1000);
  buzzlerWylacz();
  przyciskiPobierzZdarzenia();
}

int main(void) {

  diodyInit();
  przyciskiInit();
  buzzlerInit();
  sei();
  zegarInit();

  Stan stanAktualny = USTAWIANIE;
  Gracze naKimZakonczono = GRACZ_1;

  pokazStan(stanAktualny);
  while (1) {
    uint8_t zdarzenia = przyciskiPobierzZdarzenia();

    if (zdarzenia != 0) {
      switch (stanAktualny) {
      case USTAWIANIE:
        // buttony:
        // przycisk1 = dodawanie czasu
        // przycisk2 = odejmowanie czasu
        if (zdarzenia & ZDARZENIE_GRACZ_1) {
          czasUstaw(czasPobierzUstawiony() + 1);
          buzzlerWlacz(100);
          _delay_ms(100);
          buzzlerWylacz();
        }
        if (zdarzenia & ZDARZENIE_GRACZ_2) {
          czasUstaw(czasPobierzUstawiony() - 1);
          buzzlerWlacz(900);
          _delay_ms(100);
          buzzlerWylacz();
        }
        if (zdarzenia & ZDARZENIE_START) {
          stanAktualny = STOP;
        }
        pokazStan(USTAWIANIE);
        break;
      case STOP:
        if (zdarzenia & ZDARZENIE_START) {
          stanAktualny = RUCH_GR_1;
        }
        break;
      case RUCH_GR_1:
        if (zdarzenia & ZDARZENIE_GRACZ_1) {
          naKimZakonczono = GRACZ_1;
          stanAktualny = RUCH_GR_2;
        }
        if (zdarzenia & ZDARZENIE_PODDANIE) {
          pokazPoddanie();
          stanAktualny = USTAWIANIE;
        }
        break;

      case RUCH_GR_2:
        if (zdarzenia & ZDARZENIE_GRACZ_2) {
          naKimZakonczono = GRACZ_2;
          stanAktualny = RUCH_GR_1;
        }
        if (zdarzenia & ZDARZENIE_PODDANIE) {
          pokazPoddanie();
          stanAktualny = USTAWIANIE;
        }
        break;

      case PODDANIE:
        break;
      }

      pokazStan(stanAktualny);
    }
    _delay_ms(30);
    przyciskiReset();
  }

  return 0;
}
