#include<iostream>
#include<string>
using namespace std;

class C1 {
    private: 
        virtual void f(){ cout << "test " <<endl ;}
        friend class A;
        friend class B;

    public:
        virtual void mc1();
};
class C2 : public virtual C1 {
    public: 
        using C1::f ;
        virtual void mc2();
};

void C1::mc1(){
    C1 *c1; c1->f();  // C1 -> C1 : OK
    C2 *c2; c2->f();  // C1 -> C2 : OK
}

void C2::mc2(){
    C1 *c1; c1->f();  // C2 -> C1 : Pas Ok -> Private
    C2 *c2; c2->f();  // C2 -> C2 : Pas Ok -> Private
}
    
class A{
    public:
        virtual void ma(){
            C1 *c1; c1->f(); // A -> C1 : Ok -> Friend
            C2 *c2; c2->f(); // '''
        }
};

class B : public virtual A {
    public:
        virtual void mb(){
            C1 *c1; c1->f();  // '''
            C2 *c2; c2->f();  // '''
        }
};

class D {
    public:
        virtual void md(){
            C1 *c1; c1->f(); // D->C1 : Pas ok private
            C2 *c2; c2->f(); // '''
        }
};

int main(){
    C1 *c1; c1->f(); // Main -> C1 : Pas ok PRivate
    C2 *c2; c2->f(); // ''''
}