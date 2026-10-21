#ifndef BITOPS_H
#define BITOPS_H

/* NOTE:
 * Podstawowe operacje na bitach
 * BIT -> maska z jedynka na pozycji n
 * SET_BIT -> ustawienie bita na pozycji n na 1
 * CLR_BIT -> zerowanie bita na pozycji n
 * TOGGLE_BIT -> odwrocenie bita (1->0, 0->1)
 * READ_BIT -> zwraca wartosc bitu (0 lub 1)
 * IS_SET -> sprawdza czy bit jest ustawiony
 * IS_CLR -> sprawdza czy bit jest wyzerowany
 *
 * NOTE:
 * -------------- maski ------------
 * SET_MASK -> ustawia bity maski na 1
 * CLR_MASK -> zeruje bity maski
 * TOGGLE_MASK -> odwraca bity maski
 */

#define BIT(n) (1U << (n))

#define SET_BIT(reg, bit) ((reg) |= BIT(bit))
#define CLR_BIT(reg, bit) ((reg) &= ~BIT(bit))
#define TOGGLE_BIT(reg, bit) ((reg) ^= BIT(bit))
#define READ_BIT(reg, bit) (((reg) >> (bit)) & 1U)
#define IS_SET(reg, bit) (((reg) & BIT(bit)) != 0U)
#define IS_CLR(reg, bit) (((reg) & BIT(bit)) == 0U)

#define SET_MASK(reg, mask) ((reg) |= (mask))
#define CLR_MASK(reg, mask) ((reg) &= ~(mask))
#define TOGGLE_MASK(reg, mask) ((reg) ^= (mask))

#endif // BITOPS_H
