#include "test_fonctions.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/time.h>
#include <sys/resource.h>

infos_t test_fonction(SECG_t fct, unsigned int a, unsigned int b, unsigned int nb_tests) {
  unsigned int i;
  infos_t res;
  struct rusage usage_debut, usage_fin;

  assert(nb_tests > 0);

  res.resultat = 0;
  res.temps_ms = 0;
  res.memoire_ko = 0;

  /* Etat des ressources avant les tests */ 
  if (getrusage(RUSAGE_SELF, &usage_debut)) {
    perror("test_fonction");
    exit(1);
  }

  for (i = 0; i < nb_tests; ++i) {
    unsigned int r;
    r = fct(a, b);
    res.resultat = r;
  }

  /* Etat des ressources après les tests */
  if (getrusage(RUSAGE_SELF, &usage_fin)) {
    perror("test_fonction");
    exit(1);
  }

  res.temps_ms = usage_fin.ru_utime.tv_sec * 1000;
  res.temps_ms += usage_fin.ru_utime.tv_usec / 1000;
  res.temps_ms -= usage_debut.ru_utime.tv_sec * 1000;
  res.temps_ms -= usage_debut.ru_utime.tv_usec / 1000;
  res.memoire_ko = usage_fin.ru_maxrss - usage_debut.ru_maxrss;
  return res;
}
