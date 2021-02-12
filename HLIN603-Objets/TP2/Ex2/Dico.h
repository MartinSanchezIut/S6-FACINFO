#ifndef dico_h 
#define dico_h

using namespace std;
#include<iostream>
#include"Assoc.h"

template<typename dCle, typename dVal>
class Dico {
    private:
        Assoc** list;        
        int size;

    public:
        Dico();
        virtual ~Dico();

        virtual bool estVide()const;
        virtual int getSize()const;

        virtual dVal get(dCle c)const;
        virtual Assoc getIndex(int i)const;

        virtual void put(dCle c, dVam v);
        virtual void put(Assoc);

        virtual Assoc pop(dCle c);
        virtual Assoc pop(int i);

        virtual bool contains(dCle c)const;

        virtual void affiche(ostream& os)const;

        void operator=(const Assoc);
        ostream& operator<<(ostream&, const Assoc<dCle, dVal>);
};


#endif