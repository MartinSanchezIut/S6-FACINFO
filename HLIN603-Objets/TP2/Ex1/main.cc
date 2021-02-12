#include<iostream>
#include<string>
#include<unistd.h>

using namespace std;

#ifndef compte_cc
#include"CompteBancaire.cc"
#endif
#ifndef compteD_cc
#include"CompteDepot.cc"
#endif
#ifndef compteR_cc
#include"CompteRemunere.cc"
#endif
#ifndef compteDR_cc
#include"CompteDepotR.cc"
#endif

int main() {

    CompteBancaire list[] = 
        {
            CompteBancaire(100),
            CompteDepot(500),
            CompteRemunere(1000),
            CompteDepotR(12, 10),
        };

    for (size_t i = 0; i < 4; i++)    {
        cout << "---------------------------------"<<endl;
        list[i].affiche(cout) ;
        list[i].deposer(10.2) ;
        list[i].affiche(cout) ;

        usleep(50);  
    }    
    usleep(100);  
}