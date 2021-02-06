GPP=g++
SRC=CompteBancaire.cc CompteDepot.cc CompteRemunere.cc main.cc
OBJ=$(SRC:%.cc=%.o)
EXE=mainCompte

all: $(OBJ)
	$(GPP) -o $(EXE) $(OBJ)

clean:
	rm -f *~ *.o $(EXE)

.SUFFIXES: .cc .o

%.o: %.cc
	$(GPP) -c $<