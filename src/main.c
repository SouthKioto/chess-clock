#include "bitops.h"
#include "diody.h"
#include "pin_conf.h"
#include "przyciski.h"

#include <avr/interrupt.h>
#include <util/delay.h>

typedef enum { STOP, RUCH_GR_1, RUCH_GR_2, PODDANIE } Stan;
typedef enum { GRACZ_1, GRACZ_2 } Gracze;

/*
  L.yellow    - rund. gr. 1
  L.orange    - rund. gr. 2
  L.czerwona  - START/PAUZA
  L.white     - PODDANIE

  przypadek testowy:
  1. przycisniecie start (gasnie l.red)
  2. runda gracza 1 (swieci L.yellow)
  3. przyciska gracz 1 (zmiana na L.orange)
  4. przyciska gracz 2 (zmana na l.yellow)
  5. przyciska pauza (zaswieca sie l.red)
  6. przyciska pauza (gasnie l.red)
  7. przyciska poddanie (zaswieca sie l.white -> reset wszystkiego)

 */

static void pokazStan(Stan stan) {
  CLR_BIT(LED1_PORT, LED1_PIN);
  CLR_BIT(LED2_PORT, LED2_PIN);
  CLR_BIT(LED3_PORT, LED3_PIN);
  CLR_BIT(LED4_PORT, LED4_PIN);

  switch (stan) {
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
  _delay_ms(1000);
  // wyrzucenie klikniec z czasu swiecenia bialej
  przyciskiPobierzZdarzenia();
}

int main(void) {

  diodyInit();
  przyciskiInit();
  sei();

  Stan stanAktualny = STOP;
  Gracze naKimZakonczono = GRACZ_1;

  pokazStan(stanAktualny);
  while (1) {

    uint8_t zdarzenia = przyciskiPobierzZdarzenia();

    if (zdarzenia != 0) {

      switch (stanAktualny) {
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
          stanAktualny = STOP;
        }
        break;

      case RUCH_GR_2:
        if (zdarzenia & ZDARZENIE_GRACZ_2) {
          naKimZakonczono = GRACZ_2;
          stanAktualny = RUCH_GR_1;
        }
        if (zdarzenia & ZDARZENIE_PODDANIE) {
          pokazPoddanie();
          stanAktualny = STOP;
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
