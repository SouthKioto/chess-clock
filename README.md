# Zegar szachowy (AVR / Arduino Uno)

Zegar szachowy w C na ATmega328P (Arduino Uno). Projekt jest w trakcie budowy.

![Schemat układu](img/uklad.png)

## Status

- [x] Konfiguracja pinów (`pin_conf.h`) i własne makra bitowe (`bitops.h`)
- [x] Test sprzętu: miganie diodą LED na PD2 (D2)
- [x] utworzenie schematow blokowych

### TODO:

- [ ] zmiana nazw makr/zmiennych na polski

### Zadania A:

- [ ] Podłączenie przycisków i obsługa przerwan
- [ ] Podłączenie buzzlera
- [ ] Ustawienie czasu przed partią
- [ ] Przełączanie czasu miedzy graczami

### Zadania B:

- [ ] Podłączenie diod i odliczanie czasu na przerwaniu timera
- [ ] Podłączenie wyświetlacza LCD i wyświetlanie czasu oraz komunikatow
- [ ] Pauza i wznowienie
- [ ] Poddanie partii i koniec czasu

## Struktura projektu

```
.
├── img/
│   └── uklad.png      # schemat połączeń
├── include/
│   ├── bitops.h       # makra do operacji na bitach
│   ├── gpio.h         # obsługa portów GPIO
│   └── pin_conf.h     # konfiguracja pinów i F_CPU
├── src/
│   └── main.c         # punkt wejścia programu
└── README.md
```

## Konfiguracja

Piny i taktowanie ustawia się w `include/pin_conf.h`:

```c
#define LED_DDR   DDRD
#define LED_PORT  PORTD
#define LED_PIN   PD2
```

`F_CPU` domyślnie wynosi `16000000UL` (Arduino Uno). Można go nadpisać flagą kompilatora.
Piny definiowane są przez nazwy portów (PD2), a nie numery Arduino (D2), dzięki czemu kod jest przenośny między Uno a gołą ATmega328P.

## Schemat połączeń (aktualny)

| Element    | Połączenie           |
| ---------- | -------------------- |
| Anoda LED  | D2 (PD2)             |
| Katoda LED | rezystor 220 Ω → GND |

## Makra z `bitops.h`

| Makro                                   | Opis                                          |
| --------------------------------------- | --------------------------------------------- |
| `BIT(n)`                                | maska z jedynką na pozycji `n`                |
| `SET_BIT(reg, bit)`                     | ustawia bit na 1                              |
| `CLR_BIT(reg, bit)`                     | zeruje bit                                    |
| `TOGGLE_BIT(reg, bit)`                  | odwraca bit                                   |
| `READ_BIT(reg, bit)`                    | zwraca wartość bitu (0 lub 1)                 |
| `IS_SET` / `IS_CLR`                     | sprawdza, czy bit jest ustawiony / wyzerowany |
| `SET_MASK` / `CLR_MASK` / `TOGGLE_MASK` | operacje na wielu bitach naraz                |

## Templatka pin_conf.h (mozna nazwe zmenic tylko dodac do .gitignore)

```
#ifndef PIN_CONF_H
#define PIN_CONF_H

#include <avr/io.h>

#ifndef F_CPU
#define F_CPU 16000000UL
#endif // !F_CPU

/**
 * Wazny plik: tutaj beda znajdowac sie potrzebne
 * definicje pinow dla skalowalnosci aplikacji
 * oraz taktowanie ma byc przed bibl. <util/delay.h>
 *
 * ! TEN PLIK JEST TYLKO TEMPLATKĄ zmieniamy z .txt na .h
 * i bindujemy odpowiednie makra na cele naszego projektu/płytki
 *
 * Plytka: Arduino Uno
 * Piny 0-7   -> port D (PD0-PD7)
 * Piny 8-13  -> port B (PB0-PB5)
 * Piny A0-A5 -> port C (PC0-PC5)
 */

// REJESTRY PORTOW

// INFO: wejscie/wyjscie (1 = wyjscie, 0 = wejscie)
#define KIERUNEK_SZYNA_B DDRB
#define KIERUNEK_SZYNA_C DDRC
#define KIERUNEK_SZYNA_D DDRD

// INFO: zapis stanu (wyjscie) lub pull-up (wejscie)
#define STAN_PORT_B PORTB
#define STAN_PORT_C PORTC
#define STAN_PORT_D PORTD

// INFO: odczyt aktualnego stanu pinow
#define ODCZYT_PORT_B PINB
#define ODCZYT_PORT_C PINC
#define ODCZYT_PORT_D PIND

// DIODY LED (wyjscia)

// INFO: dioda 1 - pin 2
#define LED1_DDR DDRD
#define LED1_PORT PORTD
#define LED1_PIN PD2

// INFO: dioda 2 - pin 4
#define LED2_DDR DDRD
#define LED2_PORT PORTD
#define LED2_PIN PD4

// INFO: dioda 3 - pin 7
#define LED3_DDR DDRD
#define LED3_PORT PORTD
#define LED3_PIN PD7

// INFO: wbudowana dioda "L" - pin 13
#define LED_L_DDR DDRB
#define LED_L_PORT PORTB
#define LED_L_PIN PB5

// INFO: przycisk 1 - pin 3 (INT1, mozna obsluzyc przerwaniem)
#define BTN1_DDR DDRD
#define BTN1_PORT PORTD
#define BTN1_PIN PIND
#define BTN1_BIT PD3

#endif // !PIN_CONF_H

```
