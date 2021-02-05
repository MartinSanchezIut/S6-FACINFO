#include<iostream>
#include<string>

using namespace std;

class CompteBancaire {
    float solde;

    public:
        CompteBancaire(){ solde = 0;}

        virtual ~CompteBancaire(){ cout << "Solde: " << solde << endl;} 

        int getSolde() const { return solde;}

        virtual void setSolde(float s) {solde = s;}

        virtual void deposer(float s){
            setSolde(getSolde() + s) ;
        }
        

        virtual void affiche(ostream& os) const {
            os << solde ;
        }

};