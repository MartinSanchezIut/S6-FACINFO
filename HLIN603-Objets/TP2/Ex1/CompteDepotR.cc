#include<string>
#include<iostream>

using namespace std;

#ifndef compteDR_cc
#define compteDR_cc
#endif

#ifndef compteD_cc
#include"CompteDepot.cc"
#endif
#ifndef compteR_cc
#include"CompteRemunere.cc"
#endif

class CompteDepotR : virtual public CompteDepot, virtual public CompteRemunere{

    public:
        CompteDepotR(){}
        CompteDepotR(int bonus, int bonus2) {
            CompteDepot::interet = bonus; 
            CompteRemunere::interet = bonus2;
        }

        virtual ~CompteDepotR(){ 
            cout << "Destruction Solde: (CR) " << getSolde() + 
                (getSolde() * CompteRemunere::interet/100) - CompteDepot::interet << endl;
        } 

        virtual void deposer(float s)  {    // : deposer(s + (s*0.01))   
		    solde = (getSolde() + (s + (s*0.01)));

            if (s < 1000.0) {
                solde = (getSolde() - 1);
            }else {
                solde = (getSolde() + 10);
            }
        }

        virtual void affiche(ostream& os) const {
            os << getSolde() << " ("<< CompteRemunere::interet << "%)" << endl ;
        }

};