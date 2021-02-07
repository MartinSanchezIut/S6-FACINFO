#include <iostream>
#include <string>

#ifndef StropheNaze_h 
#define StropheNaze_h

#include"Oeuvre.h"

class OeuvreNaze : public virtual Oeuvre  {
    private:
		string nom;
		int annee;

    public:
		OeuvreNaze();
		OeuvreNaze(string desc, string n, int annee);  

        virtual ~OeuvreNaze();

        string getNom()const;
        virtual void setNom(string n);

        int getAnnee()const;
        virtual void setAnnee(int an);

        virtual void saisie(istream& is);
        virtual void affiche(ostream& os)const;
};
#endif