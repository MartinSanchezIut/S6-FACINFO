#include<string>
#include<iostream>

using namespace std;

#ifndef compteR_cc
#define compteR_cc
#endif

#ifndef compte_cc
#include"CompteBancaire.cc"
#endif

class CompteRemunere : virtual public CompteBancaire{
    protected:
        int interet = 10; //En pourcents

    public:
        CompteRemunere() : CompteBancaire(){}
        CompteRemunere(int bonus) : CompteBancaire(){ interet = bonus; }

        virtual ~CompteRemunere(){ 
            cout << "Destruction Solde: (CR) " << getSolde() + (getSolde() * interet/100) << endl;
        } 

        virtual void deposer(float s)  {    // : deposer(s + (s*0.01))
            solde = (getSolde() + (s + (s*0.01)));
        }

        virtual void affiche(ostream& os) const {
            os << getSolde() << " ("<< interet << ")" << endl ;
        }

};