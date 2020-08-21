/*
    template_vector.cpp

    Revision History:
*/

#include <iostream>
#include <utility>
#include <memory>

using namespace std;

/****************************************
*           CLASS DEFINITIONS
****************************************/
/*
template<typename T> class allocator{
public:
	T* allocate(int n);				// allocate space for n objects of type T
	void deallocate(T* p, int n);	// deallocate n objects of type T starting at p

	void construct(T* p, const T& v);	// construct a T with value v in p
	void destroy(T* p);				// destroy the T in p
};
*/

//struct out_of_range{/*...*/};		// class used to report range access errors
/*
template<typename T, typename A>
struct vector_base{
	A alloc;		// allocator
	T* elem;		// start of allocation
	int sz;			// number of elements
	int space;		// amount of allocated space

	vector_base(const A& a, int n)
		: alloc{a}, elem{alloc.allocate(n)}, sz{n}, space{n}{}
	~vector_base(){alloc.deallocate(elem, space);}
};

template<class T, class A>
void swap(vector_base<T,A>& a, vector_base<T,A>& b);
*/
// an almost real vector of Ts:
template<typename T, typename A = allocator<T>>
class vector{		// read "for all types T" (just like in math)
	A alloc;						// use allocate to handle memory for elements
	int sz;							// the size
	T* elem;						// a pointer to the elements
	int space;						// size + free space
public:
	vector() : sz{0}, elem{nullptr}, space{0}{}
	explicit vector(int s)					// constructor
		:sz{s},						// initialize sz
		elem{new T[s]},				// initialize elem
		space{s}					// initialize space
		{
			for(int i=0; i<sz; ++i) elem[i] = 0;	// initialize elements
		}

	vector(const vector& a)	// copy constructor
		:sz{a.sz}, elem{new T[a.sz]}, space{a.space}
		{
			copy(a.elem, a.elem+a.sz, elem);	// std::copy()
		}
	vector& operator=(const vector& a);	// copy assignment

	vector(vector&& a)	// move a to this vector
		:sz{a.sz}, elem{a.elem},	// copy a's elem and sz
		space{a.space}
		{
			a.sz = 0;			// make a the empty vector
			a.elem = nullptr;
		}
	vector& operator=(vector&& a);	// move assignment

	T& at(int n);				// checked access
	const T& at(int n) const;	// checked access

	~vector() 						// destructor
		{delete[] elem;}			// free memory

	T& operator[](int n){			// return reference
		return elem[n];
	}				
	const T& operator[](int n) const{return elem[n];}	// for const vectors

	int size() const{ return sz; }	// the current size
	int capacity() const{return space;}

	void reserve(int newalloc);
	void resize(int newsize, T def = T());
	void push_back(const T& val);
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
    vector<double> v{10};
    
    cout << v.size() << endl;

    vector<double> v2 = v;

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

template <typename T, typename A> 
vector<T,A>& vector<T,A>::operator=(const vector& a){	// make this vector a copy of a
	if(this == &a) return *this;	// self-assignment, no work needed

	if(a.sz <= space)	// enough space, no need for new allocation
	{
		for(int i=0; i<a.sz; ++i) elem[i] = a.elem[i];	// copy elements
		sz = a.sz;
		return *this;
	}

	T *p = new T[a.sz];		// allocate new space
	for(int i=0; i<a.sz; ++i)
		p[i] = a.elem[i];				// copy elements
	delete[] elem;						// deallocate old space
	space = sz = a.sz;					// set new size
	elem = p;							// now we can reset elem
	return *this;						// return a self-reference
}

template <typename T, typename A> 
vector<T,A>& vector<T,A>::operator=(vector&& a){	// move a to this vector
	delete[] elem;		// deallocate old space
	elem = a.elem;		// copy a's elem and sz
	sz = a.sz;
	a.elem = nullptr;	// make a the empty vector
	a.sz = 0;
	return *this;		// return a self-reference
}

template<typename T, typename A>
void vector<T,A>::reserve(int newalloc){
	if(newalloc <= space) return;		// never decrease allocation
	T* p = alloc.allocate(newalloc);	// allocate new space
	for(int i=0; i<sz; i++) alloc.construct(&p[i], elem[i]);	// copy
	for(int i=0; i<sz; i++) alloc.destroy(&elem[i]);			// destroy
	elem = p;
	space = newalloc;
}

template <typename T, typename A> 
void vector<T,A>::resize(int newsize, T val)
	// make the vector have newsize elements
	// initialize each new element with the default value 0.0
{
	reserve(newsize);
	for(int i=sz; i<newsize; i++)
		alloc.construct(&elem[i], val);	// construct
	for(int i=newsize; i<sz; i++)
		alloc.destroy(&elem[i]);		// destroy
	sz = newsize;
}

template <typename T, typename A> 
void vector<T,A>::push_back(const T& val)
	// increase vector size by one; initialize the new elements with d
{
	if(space == 0)
		reserve(8);		// start with space for 8 elements
	else if(sz == space)
		reserve(2*space);				// get more space
	alloc.construct(&elem[sz], val);	// add val at end
	++sz;								// increase the size
}

template<typename T, typename A> T& vector<T,A>::at(int n)
{
	if(n<0 || sz<=n) throw out_of_range();
	return elem[n];
}

template<typename T, typename A> const T& vector<T,A>::at(int n) const
{
	if(n<0 || sz<=n) throw out_of_range();
	return elem[n];
}
