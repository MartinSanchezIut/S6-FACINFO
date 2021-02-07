#include <iostream>
#include <string>

using namespace std;

#include"Oeuvre.h"

#ifndef Sale_cc
#define Sale_cc
#endif

class Sale {
    private:
        int capacite = 10;
        Oeuvre **listeOeuvre ;
    public:
        Sale() { 
            listeOeuvre = new Oeuvre*[10] ;
        }
        Sale(int c) { 
            capacite = c;
            listeOeuvre = new Oeuvre*[c] ;
        }

        void ajouter(Oeuvre *o, int i) {
            listeOeuvre[i] = o;
        }

        Oeuvre* retirer(int i) {
            Oeuvre *o = listeOeuvre[i] ;
            listeOeuvre[i] = NULL;
            return o;
        }

        void print(ostream& os) {
            int count = 0;
            for (size_t i = 0; i < capacite; i++)            {
                if (listeOeuvre[i] != NULL) {
                    listeOeuvre[i]->affiche(os);
                    count++;
                }else {
                    os << "- Empty .." << endl;
                }
            }
            os << " Capacity: " << count << " / " << capacite << endl;
        }



};
