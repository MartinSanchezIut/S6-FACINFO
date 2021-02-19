#include<iostream>
#include<string>
using namespace std;

class C1 {
    protected: 
        virtual void f(){ cout << "test " <<endl ;}
        friend class A;
        friend class B;

    public:
        virtual void mc1();
};
class C2 : public virtual C1 {
    protected: 
        virtual void f(){cout << "test " <<endl ;}
    public:
        virtual void mc2();
        friend class D;
};

void C1::mc1(){
    C1 *c1; c1->f();  // C1 -> C1 : OK
    C2 *c2; c2->f();  // C1 -> C2 : Pas ok car protected dans C2
}                             

void C2::mc2(){
    C1 *c1; c1->f();  // C2 -> C1 : Pas Ok car redefini
    C2 *c2; c2->f();  // C2 -> C2 : Ok
}
    
class A{
    public:
        virtual void ma(){
            C1 *c1; c1->f(); // A -> C1 : Ok -> Friend
            C2 *c2; c2->f(); // A -> C2 : pas ok car pas ami
        }
};

class B : public virtual A {
    public:
        virtual void mb(){
            C1 *c1; c1->f();  // B -> C1 : Ok car ami
            C2 *c2; c2->f();  // B -> C2 : pas ok car pas ami
        }
};

class D {
    public:
        virtual void md(){
            C1 *c1; c1->f(); // D->C1 : Pas ok protected
            C2 *c2; c2->f(); // D->C2 : ok ami
        }
};

int main(){
    C1 *c1; c1->f(); // Main -> C1 : Pas ok protected
    C2 *c2; c2->f(); // ''''
}