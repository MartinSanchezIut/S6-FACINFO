#include<iostream>
#include<string>

using namespace std;

#ifndef CompteRemunere.cc
#include"CompteRemunere.cc"
#endif

class CompteRCarte : virtual public CompteRemunere{

    public:
        CompteRCarte() : CompteRemunere(){}

        virtual ~CompteRCarte(){ cout << "Destruction Solde : (CRC) " << getSolde() - 5 << endl;} 

        virtual void deposer(float s, int devise){
            if (devise == 10) {
                solde = (getSolde() + s + s*0.1);
            }
        }

        virtual void affiche(ostream& os) const {
            os << getSolde() ;
        }

};