/*
    GraphicsClassDesignDrill.cpp

    Revision History:
*/

#include "../std_lib_facilities.h"

/****************************************
*           CLASS DEFINITIONS
****************************************/

class B1{
public:
    virtual void vf(){cout<<"B1::vf()\n";}
    void f(){cout<<"B1::f()\n";}
    virtual void pvf() =0;
};

class D1 : public B1{
public:
    void vf() override{cout << "D1::vf()\n";}
    void f(){cout << "D1::f()\n";}
    void pvf(){cout << "D1::pvf()\n";}
};

class D2 : public D1{
public:
    void pvf(){cout << "D2::pvf()\n";}
};

class B2{
public:
    virtual void pvf() = 0;
};

class D21 : public B2{
public:
    D21():s{"hello\n"}{}
    void pvf(){cout << s;}
private:
    string s;
};

class D22 : public B2{
public:
    D22():num{1}{}
    void pvf(){cout<<num<<'\n';}
private:
    int num;
};

/****************************************
*           FUNCTION PROTOTYPES
****************************************/

void f(B2& object){
    object.pvf();
}

/****************************************
*             MAIN FUNCTION
****************************************/

int main(){
    try{
        //B1 base;
        D1 derived1;
        B1& ref{derived1};
        D2 derived2;

        //base.vf();
        //base.f();

        derived1.vf();
        derived1.f();

        ref.vf();
        ref.f();

        derived2.vf();
        derived2.f();
        derived2.pvf();

        D21 derived21;
        D22 derived22;

        f(derived21);
        f(derived22);
    }
    catch(exception& e){
        cerr << e.what() << '\n';
        keep_window_open("~~");
        return 1;
    }
    catch(...){
        cerr << "exception\n";
        keep_window_open("~~");
        return 2;
    }
    return 0;
}

/****************************************
*           FUNCTIONS - CLASSES
****************************************/
