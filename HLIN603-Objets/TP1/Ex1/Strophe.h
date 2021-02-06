#ifndef Strophe_h 
#define Strophe_h

class Strophe {
    private:
        Vers** suiteVers;
        int nbVers;

    public:
        Strophe();

        virtual ~Strophe();

        virtual Vers* getVers(int i)const;


        virtual void saisie(istream& is);
        virtual void affiche(ostream& os)const;
       
};
#endif