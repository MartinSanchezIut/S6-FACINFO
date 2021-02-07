#include <iostream>
#include <string>

using namespace std;

#include"OeuvreNaze.h"
#include"Oeuvre.h"

OeuvreNaze::OeuvreNaze() : Oeuvre::Oeuvre() {
    nom = "Inconnu";
    annee = -1;
}

OeuvreNaze::OeuvreNaze(string desc, string n, int an) : Oeuvre::Oeuvre(desc) {
    nom = n;
    annee = an;
}

OeuvreNaze::~OeuvreNaze() {}

string OeuvreNaze::getNom()const { return nom; }

void OeuvreNaze::setNom(string n) {
    nom  = n ;
}

int OeuvreNaze::getAnnee()const { return annee; }

void OeuvreNaze::setAnnee(int n) {
    annee  = n ;
}

void OeuvreNaze::saisie(istream& is) {
    cout <<"Saisisez l'ID puis la Reference puis le Descriptif puis le Nom puis l'Annee" <<endl;
    int id, ref;
    string descriptif;
    is>>id>>ref>>descriptif>>nom>>annee;
    setID(id);
    setRef(ref);
    setDesc(descriptif);
}

void OeuvreNaze::affiche(ostream& os)const {
	os << "Id : " << getId() << " | Ref : " << getRef() << " | Desc : " << getDesc()
        << " | Nom : " << nom << "| Annee : " << annee << endl;
}

