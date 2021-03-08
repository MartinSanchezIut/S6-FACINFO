CC=gcc

OPTS=0 1 2 3
NB_TESTS=10000
MIN_N_VALUE=0
MAX_N_VALUE=100000
STEP_N_VALUE=10000

OPT=2
CFLAGS=-Wall -ansi -pedantic -g -O$(OPT)

LDFLAGS=

PROG=test_sommes
SOURCES=fonctions.c test_fonctions.c test_sommes.c
HEADERS=fonctions.h test_fonctions.h
ALGOS=Iter Rec Math OptV1 OptV2

CSV_FILES = $(foreach opt,$(OPTS),$(foreach algo,$(ALGOS),res-$(algo)-O$(opt).csv))

PNG_FILES1 = $(foreach opt,$(OPTS),valeurs-O$(opt).png)
PNG_FILES2 = $(subst valeurs,performances,$(PNG_FILES1))
PNG_FILES = $(PNG_FILES1) $(PNG_FILES2)

PROGS = $(foreach opt,$(OPTS),$(PROG)-O$(opt))

DIST_FILE=algo-txt-TP1.tgz

.PHONY: all progs csv png mostlyclean clean dist

.SUFFIXES: .c .h .o

all: png

progs: Makefile $(PROG)

csv: $(CSV_FILES)

png: $(PNG_FILES)

$(PROG): $(SOURCES:.c=-O$(OPT).o)
	@echo "- Construction du fichier $@ (avec le niveau d'optimisation $(OPT)) à partir des fichiers $^"
	@$(CC) $(LDFLAGS) $^ -o $@-O$(OPT)

$(PROGS): $(SOURCES) $(HEADERS) Makefile
	#@make --silent mostlyclean
	@echo "Construction du programme $@"
	@+make --silent OPT=$(subst O,,$(word 2,$(subst -, ,$@))) $(PROG)
	@echo

%-O$(OPT).o: %.c
	@echo "- Compilation du fichier $^ avec le niveau d'optimisation $(OPT)"
	@$(CC) $(CFLAGS) -c $< -o $@

$(CSV_FILES): $(PROGS) $(SOURCES) $(HEADERS) Makefile
	@echo "Création du fichier de statistiques $@ pour des valeurs de n allant de $(MIN_N_VALUE) à $(MAX_N_VALUE) par pas de $(STEP_N_VALUE)"
	@echo "# Date de création du Fichier: $$(date)" > "$@"
	@bash -c 'for ((n = $(MIN_N_VALUE); n <= $(MAX_N_VALUE); n+=$(STEP_N_VALUE))); do \
	  prog=$(PROG)-$(basename $(word 3,$(subst -, ,$@))); \
	  fct=$(basename $(word 2,$(subst -, ,$@))); \
	  echo "- Exécution du programme $${prog} $${fct} 0 $${n} $(NB_TESTS)";\
	  ./$${prog} $${fct} 0 $${n} $(NB_TESTS) >> "$@";\
	done'
	@echo

$(PNG_FILES): $(CSV_FILES) make-plot.gp
	@echo -e "Création des graphiques :$(patsubst %,\n- %,$(PNG_FILES))\n"
	@./make-plot.gp

dist: $(DIST_FILE)

$(DIST_FILE): Makefile make-plot.gp $(SOURCES) $(HEADERS)
	@echo "Création de l'archive $@"
	@tar -czf $@ $^

mostlyclean:
	@echo "Nettoyage du programme $(PROG), des objets et des fichiers backups"
	@rm -f $(PROG)
	@rm -f $(SOURCES:.c=-O0.o)
	@rm -f $(SOURCES:.c=-O1.o)
	@rm -f $(SOURCES:.c=-O2.o)
	@rm -f $(SOURCES:.c=-O3.o)
	@rm -f *~

clean: mostlyclean
	@echo "Nettoyage des exécutables, des fichiers de statistiques et des graphiques"
	@rm -f $(PROGS)
	@rm -f $(CSV_FILES)
	@rm -f $(PNG_FILES)
	@rm -f $(DIST_FILE)
