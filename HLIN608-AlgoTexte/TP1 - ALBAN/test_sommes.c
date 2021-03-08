#include "fonctions.h"
#include "test_fonctions.h"
#include <stdio.h>
#include <stdlib.h>
#include <libgen.h>
#include <string.h>

void usage(const char *msg, char *prog) {
  fprintf(stderr,
          "%sUsage : %s <Fonction> <a> <b> <nb_tests>\n\n"
          "Avec <Fonction> parmis 'Iter', 'Rec', 'Math', 'OptV1' ou 'OptV2'\n",
          msg, basename(prog));
  exit(1);
}

int main(int argc, char **argv) {
  const char* fct_name = NULL;
  unsigned int a;
  unsigned int b;
  unsigned int nb_tests;
  char *endptr = NULL;
  SECG_t fct;
  infos_t infos;
  
  if (argc != 5) {
    usage("mauvaise utilisation!!!\n", argv[0]);
  }
  fct_name = argv[1];
  a = strtoul(argv[2], &endptr, 10);
  if (endptr && (*endptr != '\0')) {
    usage("Erreur: le paramètre <a> doit être un entier naturel!\n", argv[0]);
  }
  b = strtoul(argv[3], &endptr, 10);
  if (endptr && (*endptr != '\0')) {
    usage("Erreur: le paramètre <b> doit être un entier naturel!\n", argv[0]);
  }
  nb_tests = strtoul(argv[4], NULL, 0);
  if (endptr && (*endptr != '\0')) {
    usage("Erreur: le paramètre <nb_tests> doit être un entier naturel!\n", argv[0]);
  }
  
  if (strcmp(fct_name, "Rec")) {
    if (strcmp(fct_name, "Iter")) {
      if (strcmp(fct_name, "Math")) {
        if (strcmp(fct_name, "OptV1")) {
          if (strcmp(fct_name, "OptV2")) {
            fct = NULL;
            usage("Erreur: le paramètre <Fonction> n'est pas valide!\n", argv[0]);
          } else {
            fct = &SommeEntiersConsecutifsGeneralOptimiseeV2;
          }    
        } else {
          fct = &SommeEntiersConsecutifsGeneralOptimiseeV1;
        }    
      } else {
        fct = &SommeEntiersConsecutifsGeneralMath;
      }    
    } else {
      fct = &SommeEntiersConsecutifsGeneralIterative;
    }   
  } else {
    fct = &SommeEntiersConsecutifsGeneralRecursive;
  }
  
  infos = test_fonction(fct, a, b, nb_tests);
  printf("#Fct\ta\tb\tres\ttps\tmem\n");
  printf("%s\t%u\t%u\t%u\t%lu\t%lu\n", fct_name, a, b, infos.resultat, infos.temps_ms, infos.memoire_ko);
  return 0;
}
