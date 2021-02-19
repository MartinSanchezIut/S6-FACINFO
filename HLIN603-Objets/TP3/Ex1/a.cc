#include<iostream>
#include<string>
using namespace std;

class C1 {
    protected: 
        virtual void f(){ cout << "test " <<endl ;}
        friend class A;
        friend class B;
        
        friend class C2; // Ajouté 
        friend class D;  // Ajouté
        friend int main();  // Ajouté pour donné l'accès dans main
    public:
        virtual void mc1();
};
class C2 : public virtual C1 {
    public: 
        virtual void mc2();
};

void C1::mc1(){
    C1 *c1; c1->f();  // C1 -> C1 : OK
    C2 *c2; c2->f();  // C1 -> C2 : OK
}

void C2::mc2(){
    C1 *c1; c1->f();  // C2 -> C1 : Pas Ok -> Friend C2
    C2 *c2; c2->f();  // C2 -> C2 : OK car héritage
}
    
class A{
    public:
        virtual void ma(){
            C1 *c1; c1->f(); 
            C2 *c2; c2->f();
        }
};

class B : public virtual A {
    public:
        virtual void mb(){
            C1 *c1; c1->f(); 
            C2 *c2; c2->f();
        }
};

class D {
    public:
        virtual void md(){
            C1 *c1; c1->f(); 
            C2 *c2; c2->f();
        }
};

int main(){
    C1 *c1; c1->f(); 
    C2 *c2; c2->f();
}