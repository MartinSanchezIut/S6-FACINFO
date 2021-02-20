#ifndef dico_h 
#define dico_h

using namespace std;
#include<iostream>
#include"Assoc.h"

template<typename dCle, typename dVal>
class Dico {
    private:
        Assoc<dCle, dVal>** list;        
        int size;

    public:
        Dico();
        virtual ~Dico();

        virtual bool estVide()const;
        virtual int getSize()const;

        virtual dVal get(dCle c)const;
        virtual Assoc<dCle, dVal> getIndex(int i)const;

        virtual void put(dCle c, dVal v);
        virtual void put(Assoc<dCle, dVal>);

        virtual Assoc<dCle, dVal> pop(dCle c);
        virtual Assoc<dCle, dVal> pop(int i);

        virtual bool contains(dCle c)const;

        virtual void affiche(ostream& os)const;

        void operator=(const Assoc<dCle, dVal>);
};
template<typename dCle, typename dVal>
ostream& operator<<(ostream&, const Assoc<dCle, dVal>);


#endif