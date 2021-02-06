#include<iostream>
#include<string>

using namespace std;

#include"Strophe.cc"

int main() {

    Strophe *s = new Strophe();
    s->saisie(cin);
    s->affiche(cout);
}
// g++ mainStrophe.cc Strophe.cc Vers.cc -I -Strophe.out