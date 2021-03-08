#ifndef __FONCTIONS_H__
#define __FONCTIONS_H__

unsigned int SommeEntiersConsecutifs(unsigned int n);


unsigned int SommeEntiersConsecutifs(unsigned int n);

/*
 * Tps : O(b - a)
 * Esp : O(b - a)
 */
unsigned int SommeEntiersConsecutifsGeneralRecursive(unsigned int a, unsigned int b);

/*
 * Tps : O(1)
 * Esp : O(1)
 */
unsigned int SommeEntiersConsecutifsGeneralMath(unsigned int a, unsigned int b);

/*
 * Tps : O(b - a)
 * Esp : O(1)
 */
unsigned int SommeEntiersConsecutifsGeneralIterative(unsigned int a, unsigned int b);

/*
 * Tps : O(1)
 * Esp : O(1)
 */
unsigned int SommeEntiersConsecutifsGeneralOptimiseeV1(unsigned int a, unsigned int b);

/*
 * Tps : O(1)
 * Esp : O(1)
 */
unsigned int SommeEntiersConsecutifsGeneralOptimiseeV2(unsigned int a, unsigned int b);

#endif
