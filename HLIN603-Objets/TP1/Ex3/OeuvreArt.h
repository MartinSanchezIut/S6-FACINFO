#include <iostream>
#include <string>

#ifndef StropheArt_h 
#define StropheArt_h

#include"Oeuvre.h"

class OeuvreArt : public virtual Oeuvre  {
    private:
		string nom;

    public:
		OeuvreArt();
		OeuvreArt(string desc, string n);  

        virtual ~OeuvreArt();

        string getNom()const;
        virtual void setNom(string n);

        virtual void saisie(istream& is);
        virtual void affiche(ostream& os)const;
};
#endif