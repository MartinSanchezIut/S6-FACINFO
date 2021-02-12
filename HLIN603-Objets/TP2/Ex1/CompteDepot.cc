#include<iostream>
#include<string>

using namespace std;

#ifndef compteD_cc
#define compteD_cc
#endif

#ifndef compte_cc
#include"CompteBancaire.cc"
#endif

class CompteDepot : virtual public CompteBancaire{
    protected:
        int interet = 100;

    public:
        CompteDepot() : CompteBancaire(){}
        CompteDepot(int taxe) : CompteBancaire(){ interet = taxe; }

        virtual ~CompteDepot(){ cout << "Destruction Solde : (CD) " << getSolde() - interet << endl;} 

        virtual void deposer(float s){
            if (s < 1000.0) {
                solde = (getSolde() + s - 1);
            }else {
                solde = (getSolde() + s + 10);
            }
        }

        virtual void affiche(ostream& os) const {
            os << getSolde() ;
        }

};