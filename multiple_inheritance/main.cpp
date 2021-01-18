#include <iostream>

class B {
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


class C {
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
typedef int (*GC)(C *);

typedef void (*S)(A *, int);
typedef void (*SC)(C *, int);

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

    cout << "--------------Method invokation through vtable for type A----------------" << endl;
    cout << "<<<<<<<<<<<<<<<<<<<<<<<Original setters / Vtable Getters>>>>>>>>>>>>>>>>>>>>>>>>>>" << endl;
    cout << "Running a->set_a(10)" << endl;
    cout << "Running a->set_b(11)" << endl;
    cout << "Running a->set_c(12)" << endl;
    a->set_a(10);
    a->set_b(11);
    a->set_c(12);
    void *a_as_b_vtable_ptr = *(void **) a; // A as B vtable address
    G *my_get_A_as_B = (G *) a_as_b_vtable_ptr; // Converting pointer to "function" table
    G my_get_b = *(my_get_A_as_B + 0); // offset 0 probably in A as B vtable
    G my_get_a = *(my_get_A_as_B + 2); // offset 2 probably in A as B vtable
    void *a_as_c_vtable_ptr = *(void **) (C *) a; // A as C vtable address
    GC *my_get_A_as_C = (GC *) a_as_c_vtable_ptr; // Converting pointer to "function" table
    GC my_get_c = *(my_get_A_as_C + 0); // offset 0 probably in A as C vtable
    cout << "Running through vtable, my_get_a()     Result: " << (*my_get_a)(a) << endl;
    cout << "Running through vtable, my_get_b()     Result: " << (*my_get_b)(a) << endl;
    cout << "Running through vtable, my_get_c()     Result: " << (*my_get_c)((C *) a) << endl;
    cout << "<<<<<<<<<<<<<<<<<<<<<<<Vtable setters / Original Getters>>>>>>>>>>>>>>>>>>>>>>>>>>" << endl;
    
    S *my_set_A_as_B = (S *) a_as_b_vtable_ptr; 
    S my_set_b = *(my_set_A_as_B + 1); // offset 1 probably in A as B vtable
    S my_set_a = *(my_set_A_as_B + 3); // offset 3 probably in A as B vtable
    
    SC *my_set_A_as_C = (SC *) a_as_c_vtable_ptr;
    SC my_set_c = *(my_set_A_as_C + 1); // offset 1 probably in A as C vtable

    cout << "Running through vtable, my_set_a(20): " << endl;
    cout << "Running through vtable, my_set_b(21): " << endl;
    cout << "Running through vtable, my_set_c(22): " << endl;
    (*my_set_a)(a, 20);
    (*my_set_b)(a, 21);
    (*my_set_c)((C *) a, 22);
    cout << "Running a->get_a()" << "    Result: " << a->get_a() << endl;
    cout << "Running a->get_b()" << "    Result: " << a->get_b() << endl;
    cout << "Running a->get_c()" << "    Result: " << a->get_c() << endl;
}

