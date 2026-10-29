#ifndef PRZYCISKI_H
#define PRZYCISKI_H

#include "bitops.h"
#include <stdint.h>

#define ZDARZENIE_GRACZ_1 BIT(0)  // 0b00000001
#define ZDARZENIE_GRACZ_2 BIT(1)  // 0b00000010
#define ZDARZENIE_START BIT(2)    // 0b00000100
#define ZDARZENIE_PODDANIE BIT(3) // 0b00001000

void przyciskiInit(void);
uint8_t przyciskiPobierzZdarzenia(void);
void przyciskiReset(void);

#endif // !PRZYCISKI_H
