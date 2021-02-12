#include<iostream>
#include<string>

#include"Assoc.h"


using namespace std;

template class Assoc<string, int>;
//template ostream& operator<<(ostream&, const Assoc<string, int>&);

int main(){
    Assoc<string, int> a = Assoc<string, int>( "Test", 4);
    Assoc<string, int>* pass = new Assoc<string, int>("Toto", 3) ;

    //cout << *pass << endl;
    //cout << a << endl;
}