#include<iostream>
#include<string>

using namespace std;

#ifndef CompteBancaire.cc
#include"CompteBancaire.cc"
#endif

class CompteRemunere : virtual public CompteBancaire{
    int interet = 10;

    public:
        CompteRemunere() : CompteBancaire(){}

        virtual ~CompteRemunere(){ cout << getSolde() + getSolde() * interet/100 << endl;} 

        virtual void deposer(float s){
            setSolde(getSolde() + (s * 0.01));
        }

        virtual void affiche(ostream& os) const {
            os << getSolde() << " ("<< interet << ")" << endl ;
        }

};