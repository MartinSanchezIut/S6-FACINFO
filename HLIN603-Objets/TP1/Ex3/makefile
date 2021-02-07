GPP=g++
SRC=Oeuvre.cc OeuvreArt.cc OeuvreNaze.cc main.cc
OBJ=$(SRC:%.cc=%.o)
EXE=mainOeuvre

all: $(OBJ)
	$(GPP) -o $(EXE) $(OBJ)

clean:
	rm -f *~ *.o $(EXE)

.SUFFIXES: .cc .o

%.o: %.cc
	$(GPP) -c $<