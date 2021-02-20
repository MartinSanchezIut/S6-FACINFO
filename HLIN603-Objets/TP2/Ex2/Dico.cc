#include<iostream>
#include<string>

using namespace std;

#include"Dico.h"

template<typename dCle, typename dVal>
Dico<dCle, dVal>::Dico() {
    list = new Assoc<dCle, dVal>*[1000];
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
dVal Dico<dCle, dVal>::get(dCle c)const {
    for (size_t i = 0; i < getSize(); i++)    {
        if (list[i].getCle() == c) {
            return list[i].getVal();
        }
    }
}

template<typename dCle, typename dVal>
Assoc<dCle, dVal> Dico<dCle, dVal>::getIndex(int i)const {
    if (i<getSize()) {
        return list[i] ;
    }
}

template<typename dCle, typename dVal>
void Dico<dCle, dVal>::put(dCle c, dVal v) {
    list[size] = new Assoc<dCle, dVal>(c, v);
    size++;
}

template<typename dCle, typename dVal>
void Dico<dCle, dVal>::put(Assoc<dCle, dVal> a) {
    list[size] = a;
    size++;
}

template<typename dCle, typename dVal>
Assoc<dCle, dVal> Dico<dCle, dVal>::pop(dCle c) {
    for (size_t i = 0; i < getSize(); i++)    {
        if (list[i].getCle() == c) {
            Assoc<dCle, dVal> ret = list[i];
            list[i] = list[size];
            size--;
            return ret;
        }
    }
}

template<typename dCle, typename dVal>
Assoc<dCle, dVal> Dico<dCle, dVal>::pop(int i) {
    if (i<getSize()) {
        Assoc<dCle, dVal> ret = list[i];
        list[i] = list[size];
        size--;
        return ret;
    }
}

template<typename dCle, typename dVal>
bool Dico<dCle, dVal>::contains(dCle c)const {
    for (size_t i = 0; i < getSize(); i++)    {
        if (list[i].getCle() == c) {
            return true;
       }
    }
    return false;
}

template<typename dCle, typename dVal>
void Dico<dCle, dVal>::affiche(ostream& os)const { 
    for (size_t i = 0; i < size; i++){
        os << list[i].affiche() << endl;
    }
}

template<typename dCle, typename dVal>
ostream& operator<<(ostream& os, const Dico<dCle, dVal>& a){     
    os << a.affiche();
    return os;
}