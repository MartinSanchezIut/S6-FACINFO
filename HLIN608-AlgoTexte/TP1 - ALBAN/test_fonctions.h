#ifndef __TEST_FONCTIONS_H__
#define __TEST_FONCTIONS_H__

typedef struct {
  unsigned int resultat;
  long unsigned int temps_ms;
  long int memoire_ko;
} infos_t;

/* SECG_t est le type correspondant à une fonction qui
   prend deux entiers non signés en paramètre et qui
   renvoie un entier non signé. */
typedef unsigned int (*SECG_t)(unsigned int, unsigned int);

infos_t test_fonction(SECG_t fct, unsigned int a, unsigned int b, unsigned int nb_tests);

#endif
