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

int main() {

    CompteBancaire list[] = 
        {
            CompteBancaire(100),
            CompteDepot(500),
            CompteBancaire(1000),
            CompteBancaire(12),
        };

    for (size_t i = 0; i < 4; i++)    {
        list[i].affiche(cout) ;
    }

    for (size_t i = 0; i < 4; i++)    {
        list[i].deposer(10.2) ;
    }  

    for (size_t i = 0; i < 4; i++)    {
        list[i].affiche(cout) ;
    }
    
    usleep(100);  
}