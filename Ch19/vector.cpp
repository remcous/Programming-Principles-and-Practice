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
	int space;						// number of elements plus "free space" / "slots"
										// for new elements ("the current allocation")
public:
	vector() : sz{0}, elem{nullptr}, space{0}{}
	explicit vector(int s)					// constructor
		:sz{s},						// initialize sz
		elem{new double[s]},			// initialize elem
		space{s}					// initialize space
		{
			for(int i=0; i<s; ++i) elem[i] = 0;	// initialize elements
		}

	vector(initializer_list<double> lst)	// initializer-list constructor
		:sz{static_cast<int>(lst.size())}, elem{new double[sz]}, space{sz}
		{
			copy(lst.begin(), lst.end(), elem);	// initialize using std::copy()
		}

	vector(const vector& a)	// allocate elements, then initialize them by copying
		:sz{a.sz}, elem{new double[a.sz]}, space{a.space}
		{
			copy(a.elem, a.elem+a.sz, elem);	// std::copy()
		}

	vector(vector&& a)	// move a to this vector
		:sz{a.sz}, elem{a.elem},	// copy a's elem and sz
		space{a.space}
		{
			a.sz = 0;			// make a the empty vector
			a.elem = nullptr;
		}

	~vector() 						// destructor
		{delete[] elem;}			// free memory

	vector& operator=(const vector& a);	// copy assignment
	vector& operator=(vector&& a);		// move assignment
	double& operator[](int n){return elem[n];}			// return reference
	const double operator[](int n) const{return elem[n];}	// for const vectors

	int size() const{ return sz; }	// the current size
	int capacity() const{return space;}

	void reserve(int newalloc);
	void resize(int newsize);
	void push_back(double d);
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

    v2[0] = 5;

    cout << v[0] << '\t' << v2[0] << endl;

    cout << v.capacity();
    v.resize(2);

    cout << ' ' << v.capacity() << '\n';
	
    return 0;
}

/****************************************
*       FUNCTION DEFINITIONS - vector
****************************************/

vector& vector::operator=(const vector& a){	// make this vector a copy of a
	if(this == &a) return *this;	// self-assignment, no work needed

	if(a.sz <= space)	// enough space, no need for new allocation
	{
		for(int i=0; i<a.sz; ++i) elem[i] = a.elem[i];	// copy elements
		sz = a.sz;
		return *this;
	}

	double *p = new double[a.sz];		// allocate new space
	for(int i=0; i<a.sz; ++i)
		p[i] = a.elem[i];				// copy elements
	delete[] elem;						// deallocate old space
	space = sz = a.sz;					// set new size
	elem = p;							// now we can reset elem
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

void vector::reserve(int newalloc){
	if(newalloc <= space) return;			// never decrease allocation
	double* p = new double[newalloc];		// allocate new space
	for(int i=0; i<sz; i++) p[i] = elem[i];	// copy old elements
	delete[] elem;							// deallocate the old space
	elem = p;
	space = newalloc;
}

void vector::resize(int newsize)
	// make the vector have newsize elements
	// initialize each new element with the default value 0.0
{
	reserve(newsize);
	for(int i=sz; i<newsize; i++) elem[i] = 0;	// initialize new elements
	sz = newsize;
}

void vector::push_back(double d)
	// increase vector size by one; initialize the new elements with d
{
	if(space == 0)
		reserve(8);	// start with space for 8 elements
	else if(sz == space)
		reserve(2*space);	// get more space
	elem[sz] = d;			// add d at end
	++sz;					// increase the size (sz is the number of elements)
}
