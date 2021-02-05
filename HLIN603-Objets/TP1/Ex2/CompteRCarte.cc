#include<iostream>
#include<string>

using namespace std;

#ifndef CompteRemunere.cc
#include"CompteRemunere.cc"
#endif

class CompteRCarte : virtual public CompteRemunere{
    int interet = 100;

    public:
        CompteRCarte() : CompteRemunere(){}

        virtual ~CompteRCarte(){ cout << getSolde() - interet << endl;} 

        virtual void deposer(float s){
            setSolde(getSolde() + s - 1);
        }

        virtual void affiche(ostream& os) const {
            os << getSolde() ;
        }

};