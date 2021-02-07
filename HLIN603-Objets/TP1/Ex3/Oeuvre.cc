#include <iostream>
#include <string>

using namespace std;

#include"Oeuvre.h"

static int countOeuvres = 1;


Oeuvre::Oeuvre() { 
	id = countOeuvres;
	ref = countOeuvres *100 +1;	
	countOeuvres++;

	descriptif = "Pas de descriptif.." ;
}
Oeuvre::Oeuvre(string desc) {
	id = countOeuvres;
	ref = countOeuvres *1000 +1;	
	countOeuvres++;

	descriptif = desc ;	
}

Oeuvre::~Oeuvre() {}

int Oeuvre::getId()const { return id; };
int Oeuvre::getRef()const { return ref; };
string Oeuvre::getDesc()const { return descriptif; };

void Oeuvre::setID(int i) { id = i ; }
void Oeuvre::setRef(int r) { ref = r ; }
void Oeuvre::setDesc(string desc) { descriptif = desc ; }

void Oeuvre::saisie(istream& is) {
    cout <<"Saisisez l'ID puis la Reference puis le Descriptif" <<endl;
    is>>id>>ref>>descriptif;
}

void Oeuvre::affiche(ostream& os)const {
	os << "Id : " << id << " | Ref : " << ref << " | Desc : " << descriptif << endl;
}
