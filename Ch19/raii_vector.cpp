/*
    raii_vector.cpp

    Revision History:
*/

#include <iostream>
#include <memory>
#include <algorithm>

using namespace std;

/****************************************
*           CLASS DEFINITIONS
****************************************/

namespace my_vector{
	template<typename T, typename A>
	struct vector_base{
	private:
		A alloc;		// allocator
		T* elem;		// start of allocation
		int sz;			// number of elements
		int space;		// amount of allocated space
	public:
		vector_base(const A& a, int n)
			:alloc{a}, elem{alloc.allocate(n)}, sz{n}, space{n}{}
		~vector_base(){alloc.deallocate(elem, space);}
	};

	template<typename T, typename A = allocator<T>>
	class vector : private vector_base<T,A>{
	public:
		// CONSTRUCTORS
		vector(): vector_base<T,A>::vector_base{alloc, 0}{}
		explicit vector(int s);

		// COPY
		vector(const vector& a);
		vector& operator=(const vector& a);

		// MOVE
		vector(vector&& a);
		vector& operator=(vector&& a);

		// ELEMENT ACCESS - CHECKED
		T& at(int n);
		const T& at(int n) const;

		// ELEMENT ACCESS - UNCHECKED
		T& operator[](int n);
		const T& operator[](int n) const;

		// private member interface
		int size() const{return vector_base<T,A>::sz;}
		int capacity() const{return vector_base<T,A>::space;}

		// MEMORY MANAGEMENT INTERFACE
		void reserve(int newalloc);
		void resize(int newsize, T val);
		void push_back(const T& val);
	private:
		// ALLOCATOR
		A alloc;
	};
}

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
    vector<int> vint{10};

    for(int i=0; i<10; i++)
    	vint.push_back(i);

    cout << vint.size() << ' ' << vint.capacity() << endl;

    vector<int> v2 = vint;

    cout << v2.size() << ' ' << v2.capacity() << endl;

    for(int i=0; i<v2.size(); i++)
    	cout << v2[i] << ' ';
    cout << endl;

    return 0;
}

/****************************************
*       FUNCTION DEFINITIONS - vector
****************************************/

template<typename T, typename A>
my_vector::vector<T,A>::vector(int s)
	: vector_base<T,A>::vector_base{alloc, s}{}

template<typename T, typename A>
my_vector::vector<T,A>::vector(const vector& a)
	:vector_base<T,A>::vector_base{alloc, a.sz}
{
	for(int i=0; i<a.sz; i++)
		this->elem[i] = a.elem[i];
}

template<typename T, typename A>
my_vector::vector<T,A>& my_vector::vector<T,A>::operator=(const vector& a)
{
	if(this == &a) return *this;	// self-assignment

	if(a.sz <= this->space) 		// enough space, no need for new allocation
	{
		for(int i=0; i<a.sz; i++) this->elem[i] = a.elem[i];
		this->sz = a.sz;
		return *this;
	}

	reserve(a.sz);
	for(int i=0; i<a.sz; i++) this->elem[i] = a.elem[i];
	this->sz = a.sz;
	return *this;
}


template<typename T, typename A>
my_vector::vector<T,A>::vector(vector&& a)
	:vector_base<T,A>::vector_base{alloc, a.sz}
{
	copy(a.elem, a.elem+a.sz, this->elem);
}

template<typename T, typename A>
my_vector::vector<T,A>& my_vector::vector<T,A>::operator=(vector&& a)
{
	// destroy and deallocate old elements
	for(int i=0; i<this->space; i++) this->alloc.destroy(&this->elem[i]);
	this->alloc.deallocate(this->elem, this->space);

	// point to a's elem, then set sz and space
	this->elem = a.elem;
	this->sz = a.sz;
	this->space = a.space;

	// remove connection to the data from a
	a.elem = nullptr;
	a.sz = 0;
	a.space = 0;

	return *this;
}

template<typename T, typename A>
T& my_vector::vector<T,A>::at(int n)
{
	if(n<0 || this->sz<=n) throw out_of_range();
	return this->elem[n];
}

template<typename T, typename A>
const T& my_vector::vector<T,A>::at(int n) const
{
	if(n<0 || this->sz<=n) throw out_of_range();
	return this->elem[n];
}

template<typename T, typename A>
T& my_vector::vector<T,A>::operator[](int n)
{
	return vector_base<T,A>::elem[n];
}

template<typename T, typename A>
const T& my_vector::vector<T,A>::operator[](int n) const
{
	return vector_base<T,A>::elem[n];
}

template<typename T, typename A>
void my_vector::vector<T,A>::reserve(int newalloc)
{
	if(newalloc <= this->space) return;			// never decrease allocation
	vector_base<T,A> b{this->alloc, newalloc};	// allocate new space
	uninitialized_copy(b.elem, &b.elem[this->sz], this->elem);	// copy
	for(int i=0; i<this->sz; i++)
		this->alloc.destroy(&this->elem[i]);	// destory old
	swap<vector_base<T,A>>(*this, b);			// swap representations
}

template <typename T, typename A> 
void my_vector::vector<T,A>::resize(int newsize, T val)
{
	reserve(newsize);
	for(int i=vector_base<T,A>::sz; i<newsize; i++)
		alloc.construct(&vector_base<T,A>::elem[i], val);	// construct
	for(int i=newsize; i<vector_base<T,A>::sz; i++)
		alloc.destroy(&vector_base<T,A>::elem[i]);		// destroy
	vector_base<T,A>::sz = newsize;
}

template <typename T, typename A> 
void my_vector::vector<T,A>::push_back(const T& val)
{
	if(vector_base<T,A>::space == 0)
		reserve(8);		// start with space for 8 elements
	else if(vector_base<T,A>::sz == vector_base<T,A>::space)
		reserve(2*vector_base<T,A>::space);		// get more space
	alloc.construct(&vector_base<T,A>::elem[vector_base<T,A>::sz], val);	// add val at end
	++vector_base<T,A>::sz;						// increase the size
}
