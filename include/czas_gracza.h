#ifndef CZAS_GRACZA_H
#define CZAS_GRACZA_H

#include <stdbool.h>
#include <stdint.h>

typedef enum { GRACZ_1, GRACZ_2 } Gracze;

bool czasUstaw(uint16_t minuty);
uint16_t czasPobierzUstawiony(void);

#endif // !CZAS_GRACZA_H
