#ifndef CZAS_GRACZA_H
#define CZAS_GRACZA_H

/**
 * @file czas_gracza.h
 * @brief Ustawianie czasu partii i liczenie ile czasu zostalo graczom.
 *
 * Ustawianie jest w minutach, a czas graczy w milisekundach.
 */

#include <stdbool.h>
#include <stdint.h>

typedef enum { GRACZ_1, GRACZ_2 } Gracze;

/**
 * @brief Ustawia czas partii.
 * @param minuty czas w minutach (1-90)
 * @return true jak sie udalo, false jak liczba jest poza zakresem
 */
bool czasUstaw(uint16_t minuty);

/**
 * @brief Zwraca ustawiony czas partii.
 * @return czas w minutach
 */
uint16_t czasPobierzUstawiony(void);

/**
 * @brief Start partii - obaj gracze dostaja ustawiony czas, zaczyna gracz 1.
 * @warning Jak zegar bedzie zerowany na starcie (zegarStart()),
 *          to trzeba go wywolac PRZED czasStart().
 */
void czasStart(void);

/**
 * @brief Zmienia gracza, ktory ma ruch.
 * @param gracz gracz, ktory teraz gra
 */
void czasPrzelacz(Gracze gracz);

/**
 * @brief Zwraca gracza, ktory ma teraz ruch.
 * @return GRACZ_1 albo GRACZ_2 (jak skonczy sie czas, to ten przegral)
 */
Gracze czasAktywny(void);

/**
 * @brief Zwraca ile czasu zostalo graczowi.
 * @param gracz ktory gracz
 * @return czas w milisekundach (nigdy ujemny)
 */
int32_t czasPobierz(Gracze gracz);

/**
 * @brief Sprawdza czy ktoremus graczowi skonczyl sie czas.
 * @return true jak skonczyl sie czas
 */
bool czasKoniec(void);

/**
 * @brief Odejmuje graczowi czas, ktory minal.
 *
 * Wolamy w kazdym obiegu petli, ale tylko jak trwa ruch gracza.
 */
void czasAktualizuj(void);

#endif // !CZAS_GRACZA_H
