#include<iostream>
#include<string>

using namespace std;

#ifndef compteDC_cc
#define compteDC_cc
#endif

#ifndef compteD_cc
#include"CompteDepot.cc"
#endif

class CompteDepotCarte : virtual public CompteDepot{
    public:
        CompteDepotCarte() : CompteDepot(){}
        CompteDepotCarte(int taxe) : CompteDepot(taxe){ }

        virtual ~CompteDepotCarte(){} 

        virtual void deposer(float s) {
            deposer(s);
        }

        virtual void affiche(ostream& os) const {
            affiche(os);
        }

};