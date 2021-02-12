#include<iostream>
#include<string>

using namespace std;

#include"Dico.h"

template<typename dCle, typename dVal>
Dico<dCle, dVal>::Dico() {
    list = new Assoc<dCle, dVal>*[10];
    size = 0;
}

template<typename dCle, typename dVal>
Dico<dCle, dVal>::~Dico() {
    if (list) 
        delete[] list;
}

template<typename dCle, typename dVal>
bool Dico<dCle, dVal>::estVide()const { return (size==0); }

template<typename dCle, typename dVal>
int Dico<dCle, dVal>::getSize()const { return size; }



template<typename dCle, typename dVal>
void Assoc<dCle, dVal>::setCle(dCle c) { cle = c; }

template<typename dCle, typename dVal>
void Assoc<dCle, dVal>::setVal(dVal v) {  valeur = v; }

template<typename dCle, typename dVal>
void Assoc<dCle, dVal>::affiche(ostream& os)const { 
    for (size_t i = 0; i < size; i++){
        os << list[i].affiche() << endl;
    }
}

template<typename dCle, typename dVal>
ostream& operator<<(ostream& os, const Dico<dCle, dVal>& a){     
    os << a.affiche();
    return os;
}