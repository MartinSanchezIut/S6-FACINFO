#include <iostream>
#include <string>

using namespace std;

#ifndef compte_cc
#define compte_cc
#endif

class CompteBancaire {
	public:
		float solde;

		CompteBancaire() { solde = 0; }
		CompteBancaire(float s) { solde = s; }

		virtual ~CompteBancaire() { cout << "Destruction solde: (CB) " << solde << endl; }

		int getSolde() const { return solde; }

		virtual void deposer(float s){
			cout << "Dépot de " << s << " e " << endl;
			float newSolde = getSolde() + s;
			cout << "Avant: " << solde << " |Après: " << newSolde << endl;
			setSolde(newSolde);
		}

		virtual void retirer(float s) {
			if (s <= solde) {
				float newSolde = solde - s;
				cout << "Retrait de " << s << " " << solde << " - " << s 
					<< " = " << newSolde << endl;
				setSolde(newSolde) ;
			}else {
				cout << "Fond insufisant !" << endl;
			}
		}

		virtual void virer(float somme, CompteBancaire* compte) {
			retirer(somme);
			compte->deposer(somme) ;
		}

		virtual void affiche(ostream &os) const	{
			os << "Solde = " << solde << endl;
		}

	private: 
		void setSolde(float s) { solde = s; }
	};