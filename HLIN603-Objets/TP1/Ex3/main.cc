#include<iostream>
#include<string>

using namespace std;

#include"Oeuvre.h"
#include"OeuvreArt.h"
#include"OeuvreNaze.h"

#ifndef Sale_cc
#include"Sale.cc"
#endif


int main() {
    /*
    Oeuvre o = Oeuvre() ;
    o.saisie(cin);
    o.affiche(cout);

    OeuvreArt o1 = OeuvreArt() ;
    o1.saisie(cin);
    o1.affiche(cout);

    OeuvreNaze o2 = OeuvreNaze() ;
    o2.saisie(cin);
    o2.affiche(cout);
    */

    Oeuvre* o = new Oeuvre("test") ;
    //o->affiche(cout);

    OeuvreArt* o1 = new OeuvreArt("test", "Piere") ;
    //o1->affiche(cout);

    OeuvreNaze* o2 = new OeuvreNaze("test", "Pipi", 12) ;
    //o2->affiche(cout);
    
    Sale s = Sale() ;
    s.print(cout);
    cout<< endl;
    s.ajouter(o, 1) ;
    s.ajouter(o1, 6) ;
    s.ajouter(o2, 7) ;

    s.print(cout);

    cout << endl;

    s.retirer(1)->affiche(cout);

    cout << endl;
    s.print(cout);


}
