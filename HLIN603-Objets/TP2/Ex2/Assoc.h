#ifndef assoc_h 
#define assoc_h

using namespace std;
#include<iostream>

template<typename dCle, typename dVal>
class Assoc {
    private:
        dCle cle;
        dVal valeur;

    public:
        Assoc(dCle c, dVal v);
        Assoc();

        virtual ~Assoc();

        virtual dCle getCle()const;
        virtual dVal getVal()const;

        virtual void setCle(dCle c);
        virtual void setVal(dVal v);      

        virtual void affiche(ostream& os)const;
       
};
template<typename dCle, typename dVal>
ostream& operator<<(ostream&, const Assoc<dCle, dVal>);

#endif