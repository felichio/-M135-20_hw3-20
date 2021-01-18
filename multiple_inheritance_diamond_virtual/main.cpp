#include <iostream>

class D {
    private:
        // int d = 6;
    public:
        int d = 6;  
        virtual int get_d();
        virtual void set_d(int);
};

int D::get_d() {
    return this->d;
}

void D::set_d(int x) {
    this->d = x;
}

class B: virtual public D {
    private:
        int b = 3;
    public:
        virtual int get_b();
        virtual void set_b(int);
};

int B::get_b() {
    return this->b;
}

void B::set_b(int x) {
    this->b = x;
}


class C: virtual public D {
    private:
        int c = 4;
    public:
        virtual int get_c();
        virtual void set_c(int);
};

int C::get_c() {
    return this->c;
}

void C::set_c(int x) {
    this->c = x;
}


class A: public B, public C {
    private:
        int a = 5;
    public:
        virtual int get_a();
        virtual void set_a(int);
};

int A::get_a() {
    return this->a;
}

void A::set_a(int x) {
    this->a = x;
}

typedef int (*G)(A *);

using namespace std;

int main(int argc, char *argv[]) {
    // Size of a pointer type in current system
    cout << "Size of a pointer type in bytes: " << sizeof(void *) << endl;
    // create an intance of A class in heap
    A *a = new A();
    // Size of an object of type A
    cout << "Size of type A object instance in bytes: " << sizeof(*a) << endl;
    
    
    // Printing A type object layout
    cout << "--------------Object Layout for type A----------------" << endl;
    cout << "A/B (primary) vtable address (address of address): " << (void **)(((char *) a) + 0) << " or " << a << endl;
    cout << "A/B (primary) vtable value (address): " << *(void **)(((char *) a) + 0) << endl;
    cout << "A.b attribute address: " << (int *)(((char *) a) + 8) << endl;
    cout << "A.b attribute value: " << *(int *)(((char *) a) + 8) << endl;
    cout << "A padding address: " << (int *)(((char *) a) + 12) << endl;
    cout << "A padding value: " << *(int *)(((char *) a) + 12) << endl;
    cout << "C (A as C) vtable address (address of address): " << (void **)(((char *) a) + 16) << " or " << (C *) a << endl; 
    cout << "C (A as C) vtable value (address): " << *(void **)(((char *) a) + 16) << endl;
    cout << "A.c attribute address: " << (int *)(((char *) a) + 24) << endl;
    cout << "A.c attribute value: " << *(int *)(((char *) a) + 24) << endl;
    cout << "A.a attribute address: " << (int *)(((char *) a) + 28) << endl;
    cout << "A.a attribute value: " << *(int *)(((char *) a) + 28) << endl;
    cout << "D (A as D) vtable address (address of address): " << (void **)(((char *) a) + 32) << endl;
    cout << "D (A as D) vtable value (address): " <<  *(void **)(((char *) a) + 32) << endl;
    cout << "A.d attribute address: " << (int *)(((char *) a) + 40) << endl;
    cout << "A.d attribute value: " <<  *(int *)(((char *) a) + 40) << endl;
    cout << "A padding address: " << (int *)(((char *) a) + 44) << endl;
    cout << "A padding value: " << *(int *)(((char *) a) + 44) << endl;
    
}

