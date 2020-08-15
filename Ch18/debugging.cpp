#include "../Libraries/std_lib_facilities.h"

struct X { // simple test class
	int val;

	void out(const string& s, int nv)
		{ cerr << this << "–>" << s << ": " << val << " (" << nv << ")\n"; }

	X(){ out("X()",0); val=0; } // default constructor
	X(int v) { val=v; out( "X(int)",v); }
	X(const X& x){ val=x.val; out("X(X&) ",x.val); } // copy constructor
	
	X& operator=(const X& a) // copy assignment
		{ out("X::operator=()",a.val); val=a.val; return *this; }
	
	~X() { out("~X()",0); } // destructor
};

X glob(2); // a global variable

X copy(X a) { return a; }

X copy2(X a) { X aa = a; return aa; }

X& ref_to(X& a) { return a; }

X* make(int i) { X a(i); return new X(a); }

struct XX { X a; X b; };

int main()
{
	cerr << "Start of main()\n";
	cerr << "X loc{4}\n";
	X loc {4}; // local variable
	cerr << "X loc2{loc}\n";
	X loc2 {loc}; // copy construction
	cerr << "loc = X{5}\n";
	loc = X{5}; // copy assignment
	cerr << "loc2 = copy(loc)\n";
	loc2 = copy(loc); // call by value and return
	cerr << "loc2 = copy2(loc)\n";
	loc2 = copy2(loc);
	cerr << "X loc3{6}\n";
	X loc3 {6};
	cerr << "X& r = ref_to(loc)\n";
	X& r = ref_to(loc); // call by reference and return
	cerr << "delete make(7)\n";
	delete make(7);
	cerr << "delete make(8)\n";
	delete make(8);
	cerr << "vector<X> v(4)\n";
	vector<X> v(4); // default values
	cerr << "XX loc4\n";
	XX loc4;
	cerr << "X* p = new X{9}\n";
	X* p = new X{9}; // an X on the free store
	cerr << "delete p\n";
	delete p;
	cerr << "X* pp = new X[5]\n";
	X* pp = new X[5]; // an array of Xs on the free store
	cerr << "delete[] pp\n";
	delete[] pp;
	cerr << "End of main()\n";
}