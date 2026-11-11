#ifndef CZAS_GRACZA_H
#define CZAS_GRACZA_H

#include <stdint.h>

typedef enum { GRACZ_1, GRACZ_2 } Gracze;

void czasUstaw(uint16_t minuty);
uint16_t czasPobierzUstawiony(void);

#endif // !CZAS_GRACZA_H
