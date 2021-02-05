#include<iostream>
#include<string>

using namespace std;

class Vers {
    string suiteMot;
    string rime;

    public:
        Vers(){}
        Vers(string sm){ suiteMot = sm;}
        Vers(string sm, string r){ suiteMot = sm; rime = r;}
        ~Vers(){}

        string getSuiteMot() const { return suiteMot;}
        void setSuiteMot(string sm) {suiteMot = sm;}
        string getRime() const { return rime;}
        void setRime(string r) { rime = r;}

        void saisie(istream& is) {
            cout << "Vers puis Rime" << endl;
            is >> suiteMot >> rime;
        }
        void affiche(ostream& os) const {
            os << suiteMot ;
        }

};
