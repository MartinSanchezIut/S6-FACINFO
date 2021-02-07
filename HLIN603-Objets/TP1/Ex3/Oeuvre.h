#include <iostream>
#include <string>

#ifndef Strophe_h 
#define Strophe_h

class Oeuvre  {
    private:
		int id;
		int ref;
		string descriptif;

    public:
		Oeuvre();
		Oeuvre(string desc);  

        virtual ~Oeuvre();

        int getId()const;
        int getRef()const;
        string getDesc()const;

        virtual void setID(int i);
        virtual void setRef(int r);
        virtual void setDesc(string s);

        virtual void saisie(istream& is);
        virtual void affiche(ostream& os)const;
};
#endif