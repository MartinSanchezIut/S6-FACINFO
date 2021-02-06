#include<iostream>
#include<string>

using namespace std;

#include"Vers.cc"

class Strophe {
    private : 
        int nbVers;
        Vers** suiteVers;

    public:
        Strophe(){ suiteVers = NULL; nbVers = 0;}
        ~Strophe(){ if(suiteVers) delete[] suiteVers; }

        Vers* vers(int i) const { 
            if (i >= 0 && i < nbVers)
                return suiteVers[i];
        }

        void saisie(istream& is) {
            if (suiteVers)
                delete[] suiteVers;

            cout << "Entrez le nombre de vers" << endl;
            is >> nbVers ;
            suiteVers = new Vers*[nbVers] ;
            for (size_t i = 0; i < nbVers; i++)
            {
                Vers *v = new Vers();
                v->saisie(is) ;
                suiteVers[i] = v;
            }
            
        }
        void affiche(ostream& os) const {
            for (size_t i = 0; i < nbVers; i++)
            {
                suiteVers[i]->affiche(os);
                os << endl;
            }
            
        }

};
