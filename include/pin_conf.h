#ifndef PIN_CONF_H
#define PIN_CONF_H

#include <avr/io.h>

#ifndef F_CPU
#define F_CPU 16000000UL
#endif // !F_CPU

/**
 * Wazny plik: tutaj bedą znajdowac sie potrzebne
 * definicje pinow dla skalowalnosci aplikacji
 * oraz taktowanie ma byc przed bibl. <util/delay.h>
 */

#define LED_DDR DDRD
#define LED_PORT PORTD
#define LED_PIN PD2

#endif // !PIN_CONF
