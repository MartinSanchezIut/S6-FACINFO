#include<iostream>
#include<string>

using namespace std;

#ifndef CompteBancaire.cc
#include"CompteBancaire.cc"
#endif

class CompteDepot : virtual public CompteBancaire{
    int interet = 100;

    public:
        CompteDepot() : CompteBancaire(){}

        virtual ~CompteDepot(){ cout << getSolde() - interet << endl;} 

        virtual void deposer(float s){
            setSolde(getSolde() + s - 1);
        }

        virtual void affiche(ostream& os) const {
            os << getSolde() ;
        }

};