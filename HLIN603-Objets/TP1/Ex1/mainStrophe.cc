#include<iostream>
#include<string>

using namespace std;

#include"Vers.h"
#include"Strophe.h"


int main() {

    Strophe *s = new Strophe();
    s->saisie(cin);
    s->affiche(cout);
}
// g++ mainStrophe.cc Strophe.cc Vers.cc -I -Strophe.out