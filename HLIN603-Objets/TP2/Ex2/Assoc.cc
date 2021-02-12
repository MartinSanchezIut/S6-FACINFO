#include<iostream>
#include<string>

using namespace std;

#include"Assoc.h"

template<typename dCle, typename dVal>
Assoc<dCle, dVal>::Assoc(dCle c, dVal v) {
    cle = c;
    valeur = v;
}

template<typename dCle, typename dVal>
Assoc<dCle, dVal>::~Assoc() { }

template<typename dCle, typename dVal>
dCle Assoc<dCle, dVal>::getCle()const { return cle; }

template<typename dCle, typename dVal>
dVal Assoc<dCle, dVal>::getVal()const { return valeur; }

template<typename dCle, typename dVal>
void Assoc<dCle, dVal>::setCle(dCle c) { cle = c; }

template<typename dCle, typename dVal>
void Assoc<dCle, dVal>::setVal(dVal v) {  valeur = v; }

template<typename dCle, typename dVal>
void Assoc<dCle, dVal>::affiche(ostream& os)const { 
    os << cle << " -> " << valeur << endl;
}

template<typename dCle, typename dVal>
ostream& operator<<(ostream& os, const Assoc<dCle, dVal>& a){ 
    a.affiche(os); return os;
}