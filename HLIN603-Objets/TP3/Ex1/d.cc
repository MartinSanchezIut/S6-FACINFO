class A : public virtual B{
    //using B::x ;
    public:
        int test() {
            x();
            y();
        }
};
class B{
    protected:
        int x() ;
    private:
        int y() ;

    public:
        int test() {
            x();
            y();
        }
};
class C{
    public:
        int test() {
            x();
            y();
        }
};

int main() {
    A *a; a->y() ;
    A *a; a->x() ;

    B *b; b->y() ;
    B *b; b->x() ;
}


