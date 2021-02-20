#include<iostream>
#include<string>

#include"Assoc.cc"
//#include"Dico.cc"

using namespace std;

/*
template class Assoc<char, int*> ;
template class Assoc<string, string> ;
template ostream& operator<<(ostream&, const Assoc<string, string>&);
template ostream& operator<<(ostream&, const Assoc<char, int*>&);
*/

int main(){
    Assoc<char, int*> a;
    Assoc<string, string>* assoc = new Assoc<string, string>("test", "4");

    cout << *assoc << endl;
    cout << a << endl;
}