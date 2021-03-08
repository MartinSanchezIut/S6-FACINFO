#include "fonctions.h"

unsigned int SommeEntiersConsecutifs(unsigned int n) {
  return SommeEntiersConsecutifsGeneralOptimiseeV2(0, n);
}

unsigned int SommeEntiersConsecutifsGeneralRecursive(unsigned int a, unsigned int b) {
  return b < a ? 0 : a + SommeEntiersConsecutifsGeneralRecursive(a + 1, b);
}

unsigned int SommeEntiersConsecutifsGeneralMath(unsigned int a, unsigned int b) {
  return (a + b) * (b - a + 1) / 2;
}

unsigned int SommeEntiersConsecutifsGeneralIterative(unsigned int a, unsigned int b) {
  unsigned int i, somme = 0;
  for (i = a; i <= b; ++i) {
    somme += i;
  }
  return somme;
}

unsigned int SommeEntiersConsecutifsGeneralOptimiseeV1(unsigned int a, unsigned int b) {
  unsigned int resultat = a + b;
  if ((a + b) % 2) {      /* (a + b) est impair, donc (b - a + 1) est pair */
    resultat = b - a + 1; /* resultat = b - a + 1 */
    resultat /= 2;        /* resultat = (b - a + 1) / 2 */
    resultat *= (a + b);  /* resultat = (b - a + 1) / 2 * (a + b) */
  } else {                  /* (a + b) est pair */
    resultat /= 2;          /* resultat = (a + b) / 2 */
    resultat *= (b - a +1); /* resultat = (a + b) / 2 * (b - a + 1) */
  }
  return resultat;
}

unsigned int SommeEntiersConsecutifsGeneralOptimiseeV2(unsigned int a, unsigned int b) {
  unsigned int resultat = a + b;
  if (resultat & 1) {     /* (a + b) est impair, donc (b - a + 1) est pair */
    resultat = b - a + 1; /* resultat = b - a + 1 */
    resultat >>= 1;       /* resultat = (b - a + 1) / 2 */
    resultat *= (a+b);    /* resultat = (b - a + 1) / 2 * (a + b) */
  } else {                   /* (a + b) est pair */
    resultat >>= 1;          /* resultat = (a + b) / 2 */
    resultat *= (b - a + 1); /* resultat = (a + b) / 2 * (b - a + 1) */
  }
  return resultat;
}
