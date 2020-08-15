/*
    vector.cpp

    Revision History:
*/

#include <iostream>

using namespace std;

/****************************************
*           CLASS DEFINITIONS
****************************************/

class vector{
	int sz;							// the size
	double* elem;					// pointer to the first element 
									// (of type double)
public:
	vector(int s)					// constructor
		:sz(s),						// initialize sz
		elem{new double[s]}			// initialize elem
		{
			for(int i=0; i<s; ++i) elem[i] = 0;	// initialize elements
		}

	vector(initializer_list<double> lst)	// initializer-list constructor
		:sz{lst.size()}, elem{new double[sz]}
		{
			copy(lst.begin(), lst.end(), elem);	// initialize using std::copy()
		}

	vector(const vector& a)	// allocate elements, then initialize them by copying
		:sz{a.sz}, elem{new double[a.sz]}
		{
			copy(a.elem, a.elem+a.sz, elem);	// std::copy()
		}

	vector(vector&& a)	// move a to this vector
		:sz{a.sz}, elem{a.elem}	// copy a's elem and sz
		{
			a.sz = 0;			// make a the empty vector
			a.elem = nullptr;
		}

	~vector() 						// destructor
		{delete[] elem;}			// free memory

	vector& operator=(const vector& a);	// copy assignment
	vector& operator=(vector&& a);		// move assignment
	double& operator[](int n){return elem[n];}			// return reference
	double operator[](int n) const{return elem[n];}	// for const vectors

	int size() const{ return sz; }	// the current size
	double get(int n) const{return elem[n];}	// access: read
	void set(int n, double v){elem[n]=v;}		// access: write
};

/****************************************
*           FUNCTION PROTOTYPES
****************************************/

/****************************************
*           GLOBAL VARIABLES
****************************************/

/****************************************
*             MAIN FUNCTION
****************************************/

int main(){
    vector v{10};

    cout << v.size() << endl;

    vector v2 = v;

    v2.set(0, 5);

    cout << v.get(0) << '\t' << v2.get(0) << endl;
	
    return 0;
}

/****************************************
*       FUNCTION DEFINITIONS - vector
****************************************/

vector& vector::operator=(const vector& a){	// make this vector a copy of a
	double *p = new double[a.sz];		// allocate new space
	copy(a.elem, a.elem + a.sz, elem);	// copy elements
	delete[] elem;						// deallocate old space
	elem = p;							// now we can reset elem
	sz = a.sz;
	return *this;						// return a self-reference
}

vector& vector::operator=(vector&& a){	// move a to this vector
	delete[] elem;		// deallocate old space
	elem = a.elem;		// copy a's elem and sz
	sz = a.sz;
	a.elem = nullptr;	// make a the empty vector
	a.sz = 0;
	return *this;		// return a self-reference
}
