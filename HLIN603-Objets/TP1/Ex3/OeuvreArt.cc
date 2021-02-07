#include <iostream>
#include <string>

using namespace std;

#include"OeuvreArt.h"
#include"Oeuvre.h"

OeuvreArt::OeuvreArt() : Oeuvre::Oeuvre() {
    nom = "Inconnu";
}

OeuvreArt::OeuvreArt(string desc, string n) : Oeuvre::Oeuvre(desc) {
    nom = n;
}

OeuvreArt::~OeuvreArt() {}

string OeuvreArt::getNom()const { return nom; }

void OeuvreArt::setNom(string n) {
    nom  = n ;
}

void OeuvreArt::saisie(istream& is) {
    cout <<"Saisisez l'ID puis la Reference puis le Descriptif puis le Nom" <<endl;
    int id, ref;
    string descriptif;
    is>>id>>ref>>descriptif>>nom;
    setID(id);
    setRef(ref);
    setDesc(descriptif);
}

void OeuvreArt::affiche(ostream& os)const {
	os << "Id : " << getId() << " | Ref : " << getRef() << " | Desc : " << getDesc()
        << " | Nom : " << nom << endl;
}

