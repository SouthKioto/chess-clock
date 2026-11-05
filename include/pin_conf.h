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

// INFO: dioda 1 (zolta) - ruch gracza 1 (pin 9)
#define LED1_DDR DDRB
#define LED1_PORT PORTB
#define LED1_PIN PB1

// INFO: dioda 2 (pomaranczowa) - ruch gracza 2 (pin 8)
#define LED2_DDR DDRB
#define LED2_PORT PORTB
#define LED2_PIN PB0

// INFO: dioda 3 (czerwona) - START/PAUZA (pin 7)
#define LED3_DDR DDRD
#define LED3_PORT PORTD
#define LED3_PIN PD7

// INFO: dioda 4 (biala) - PODDANIE (pin 12)
// (pin 6 = OC0A zostawiony wolny dla Timer0)
#define LED4_DDR DDRB
#define LED4_PORT PORTB
#define LED4_PIN PB4

// INFO: wbudowana dioda "L" (pin 13)
#define LED_L_DDR DDRB
#define LED_L_PORT PORTB
#define LED_L_PIN PB5

// INFO: buzzler - (pin 10, OC1B -> sterowany przez Timer1)
#define BUZZLER_DDR DDRB
#define BUZZLER_PORT PORTB
#define BUZZLER_PIN PB2

// PRZYCISKI (wejscia z pull-upem, wcisniety = 0, drugi styk do GND)

// INFO: przycisk 1 - gracz 1 (pin 3)
#define BTN1_DDR DDRD
#define BTN1_PORT PORTD
#define BTN1_PIN PIND
#define BTN1_BIT PD3

// INFO: przycisk 2 - gracz 2 (pin 2)
#define BTN2_DDR DDRD
#define BTN2_PORT PORTD
#define BTN2_PIN PIND
#define BTN2_BIT PD2

// INFO: przycisk 3 - START/PAUZA (pin 4)
#define BTN3_DDR DDRD
#define BTN3_PORT PORTD
#define BTN3_PIN PIND
#define BTN3_BIT PD4

// INFO: przycisk 4 - PODDANIE (pin 5)
#define BTN4_DDR DDRD
#define BTN4_PORT PORTD
#define BTN4_PIN PIND
#define BTN4_BIT PD5

#endif // !PIN_CONF_H
