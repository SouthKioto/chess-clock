# Zegar szachowy (AVR / Arduino Uno)

Zegar szachowy w C na ATmega328P (Arduino Uno). Projekt jest w trakcie budowy.

![Schemat układu](img/uklad.png)

## Status

- [x] Konfiguracja pinów (`pin_conf.h`) i własne makra bitowe (`bitops.h`)
- [x] Test sprzętu: miganie diodą LED na PD2 (D2)

### TODO:
- [ ] zmiana nazw makr/zmiennych na polski
- [ ] utworzenie schematow blokowych

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

| Element | Połączenie |
|---|---|
| Anoda LED | D2 (PD2) |
| Katoda LED | rezystor 220 Ω → GND |

## Makra z `bitops.h`

| Makro | Opis |
|---|---|
| `BIT(n)` | maska z jedynką na pozycji `n` |
| `SET_BIT(reg, bit)` | ustawia bit na 1 |
| `CLR_BIT(reg, bit)` | zeruje bit |
| `TOGGLE_BIT(reg, bit)` | odwraca bit |
| `READ_BIT(reg, bit)` | zwraca wartość bitu (0 lub 1) |
| `IS_SET` / `IS_CLR` | sprawdza, czy bit jest ustawiony / wyzerowany |
| `SET_MASK` / `CLR_MASK` / `TOGGLE_MASK` | operacje na wielu bitach naraz |
| `WRITE_FIELD(reg, mask, pos, val)` | zapis wartości do pola bitowego |
