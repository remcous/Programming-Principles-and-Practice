/*
    exercise11.cpp

    Revision History:
*/

#include <iostream>
#include <vector>

using namespace std;

/****************************************
*           CLASS DEFINITIONS
****************************************/

template<typename T> class counted_ptr{
public:
	counted_ptr():ptr{new T}, ctr{new int}{*ctr = 1;}
	counted_ptr(const T& t):ptr{new T{t}}, ctr{new int}{*ctr = 1;}

	// COPY
	counted_ptr(const counted_ptr<T>& a):ptr{a.ptr}, ctr{a.ctr}
	{
		(*ctr)++;
	}

	// MOVE
	counted_ptr(counted_ptr<T>&& a)
	{
		cout << "MOVE\n";
		ptr = a.ptr;
		ctr = a.ctr;
		a.ptr = nullptr;
		a.ctr = nullptr;
	}

	// DESTRUCTOR
	~counted_ptr(){
		(*ctr)--;
		if(ctr <= 0)
		{
			delete ptr;
			delete ctr;
		}
	}

	// INTERFACE
	int count() const{return *ctr;}

	// OPERATORS
	T operator*(){return *ptr;}
	T* operator->(){return ptr;}
	void operator=(const T& t){*ptr = t;}

	// friend I/O
	template<typename U> 
	friend ostream& operator<<(ostream& os, const counted_ptr<U>& a);
private:
	T* ptr;
	int* ctr;
};

/****************************************
*           FUNCTION PROTOTYPES
****************************************/

template<typename T> ostream& operator<<(ostream& os, const counted_ptr<T>& a);
template<typename T> void print(counted_ptr<T>& cpi);

/****************************************
*           GLOBAL VARIABLES
****************************************/

/****************************************
*             MAIN FUNCTION
****************************************/

int main(){
    try{
    	cout << "default construction: cpi\n";
        counted_ptr<int> cpi;
        print(cpi);

        cout << "Assignment: cpi = 5\n";
        cpi = 5;
        print(cpi);

        cout << "Assigned construction: cpd{3.14}\n";
        counted_ptr<double> cpd{3.14};
        print(cpd);

        {
        	cout << "\nEntering scope...\n";
        	cout << "Copy constructor: cpi_clone{cpi}\n";
        	counted_ptr<int> cpi_clone{cpi};
        	cout << "cpi...";
        	print(cpi);
        	cout << "cpi_clone...";
        	print(cpi_clone);
        	cout << "Exiting scope...\n\n";
        }

        cout << "cpi...";
        print(cpi);
    }
    catch(exception& e){
        cerr << e.what() << '\n';
        return 1;
    }
    catch(...){
        cerr << "exception\n";
        return 2;
    }
    return 0;
}

/****************************************
*       FUNCTION DEFINITIONS - GLOBAL
****************************************/

template<typename T> ostream& operator<<(ostream& os, const counted_ptr<T>& a)
{
	os << a.ptr;
}

template<typename T> void print(counted_ptr<T>& cpi)
{
	cout << cpi.count() << "x " << cpi << " : " << *cpi << endl;
}
