/*
    exercise5.cpp

    Revision History:
*/

#include "../std_lib_facilities.h"

/****************************************
*           CLASS DEFINITIONS
****************************************/

class Int{
public:
	// CONSTRUCTORS
	Int():i{0}{}			// default constructor
	Int(int val):i{val}{}	// intialize constructor

	// COPY
	Int(const Int& a):i{a.i}{}		// copy constructor
	Int& operator=(const Int& a);	// copy assignment

	// MOVE
	Int(Int&& a):i{a.i}{}
	Int& operator=(Int&& a){i=a.i;}

	// MATH OPERATIONS
	Int& operator=(const int a){i = a;}
	Int operator+(const Int rv) const;
	Int operator-(const Int rv) const;
	Int operator*(const Int rv) const;
	Int operator/(const Int rv) const;

	// CAST TO INT
	operator int() const{return i;}

	// FRIENDS I/O
	friend ostream& operator<<(ostream&, const Int&);
	friend istream& operator>>(istream&, Int&);
private:
	int i;
};

/****************************************
*           FUNCTION PROTOTYPES
****************************************/

ostream& operator<<(ostream& os, const Int& a);
istream& operator>>(istream& is, Int& a);

/****************************************
*           GLOBAL VARIABLES
****************************************/

/****************************************
*             MAIN FUNCTION
****************************************/

int main(){
    try{
        Int i;
    	cout << "default construction Int i: " << i << endl;
        Int j{10};
    	cout << "assigned construction Int j{10}: " << j << endl;

        Int k{i};		// copy construction
    	cout << "copy construction Int k{i}: " << k << endl;
        Int l = j;		// copy assignment
    	cout << "copy assignment Int l = j: " << l << endl;

        cout << "Enter a value for i: ";
        cin >> i;

        cout << "i = " << i << endl;
        cout << "j = " << j << endl;

        cout << "\nMATH OPERATIONS\n";
        cout << "i + j = " << i+j << endl;
        cout << "i - j = " << i-j << endl;
        cout << "i * j = " << i*j << endl;
        cout << "i / j = " << i/j << endl;

        double d = i;

        cout << d << endl;
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
*       FUNCTION DEFINITIONS - Int
****************************************/

ostream& operator<<(ostream& os, const Int& a)
{
	os << a.i;
}

istream& operator>>(istream& is, Int& a)
{
	is >> a.i;
}

Int Int::operator+(const Int rv) const
{
	Int temp{this->i + rv.i};
	return temp;
}

Int Int::operator-(const Int rv) const
{
	Int temp{this->i - rv.i};
	return temp;
}

Int Int::operator*(const Int rv) const
{
	Int temp{this->i * rv.i};
	return temp;
}

Int Int::operator/(const Int rv) const
{
	Int temp{this->i / rv.i};
	return temp;
}
