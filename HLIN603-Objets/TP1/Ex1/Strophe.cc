#include<iostream>
#include<string>

using namespace std;

#include"Vers.h"
#include"Strophe.h"

Strophe::Strophe() { suiteVers=NULL; nbVers=0; }

/*
Strophe::Strophe(const Strophe& autreStrophe) {
    
    nbVers=autreStrophe.nbVers;
    suiteVers=new Vers*[nbVers];
    for (int i=0; i<nbVers; i++) 
        suiteVers[i]=autreStrophe.suiteVers[i];
    
    *this=autreStrophe; 
}
*/

Strophe::~Strophe(){
    if (suiteVers) 
        delete[] suiteVers;
}

Vers* Strophe::getVers(int i)const{
    if (i>=0 && i<nbVers) 
        return suiteVers[i]; 
    else 
        return NULL;
}

void Strophe::saisie(istream& is){
  if (suiteVers) delete[] suiteVers;

  cout << "Entrer le nombre de vers : " << endl;
  is>>nbVers; 

  suiteVers = new Vers*[nbVers];
  for (int i=0; i<nbVers; i++)    {
      Vers *v = new Vers(); 
      v->saisie(is); 
      suiteVers[i]=v;
    }
}

void Strophe::affiche(ostream& os)const{
    for (int i=0; i<nbVers; i++)    {
        suiteVers[i]->affiche(os); os << endl;
    }  
}