#include<iostream>
#include<string>

using namespace std;

#ifndef CompteBancaire.cc
#include"CompteBancaire.cc"
#endif
#ifndef CompteRemunere.cc
#include"CompteRemunere.cc"
#endif
#ifndef CompteDepot.cc
#include"CompteDepot.cc"
#endif

int main() {

    CompteBancaire *s = new CompteBancaire();
    s->setSolde(10.3);
    s->affiche(cout);
    delete s;

    CompteRemunere *a = new CompteRemunere();
    a->setSolde(18.3);
    a->affiche(cout);
    delete a;

    CompteDepot *b = new CompteDepot();
    b->setSolde(130.3);
    b->affiche(cout);
    delete b;

}
// g++ mainCompte.cc CompteBancaire.cc CompteRemunere.cc CompteDepot.cc -I -Compte.out