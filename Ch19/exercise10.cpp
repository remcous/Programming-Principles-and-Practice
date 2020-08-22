/*
    exercise10.cpp

    Revision History:
*/

#include <iostream>
#include <vector>

using namespace std;

/****************************************
*           CLASS DEFINITIONS
****************************************/

template<typename T> class unique_ptr{
public:
	unique_ptr():ptr{new T}{}
	~unique_ptr(){delete ptr;}

	T operator*() const{return *ptr;}
	T* operator->() const{return ptr;}

	T* release()
	{
		T* temp = ptr;
		ptr = nullptr;
		return temp;
	}

	operator bool() const{return !(ptr == nullptr);}
private:
	T* ptr;

	// disable copy and assignment constructors
	unique_ptr(const unique_ptr&) = delete;
	T operator=(const unique_ptr&) = delete;
	unique_ptr(T*) = delete;
	unique_ptr(T&) = delete;
	unique_ptr(T) = delete;	
};

struct holder{
public:
	holder(){}
	unique_ptr<int> ptr;
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
    try{
        unique_ptr<vector<int>> p1;

        cout << "unique_ptr<vector<int>> p1...size() = " 
        	<< p1->size() << endl;

        //unique_ptr<int> p2{p1};	// error: copy constructor is private
        //unique_ptr<int> p2 = p1;	// error: copy assignment is private
        //unique_ptr<int> p2{new int};	// error: assignment is private

        p1->push_back(1);
        cout << "p1->push_back(1)...size() = " << p1->size() << endl;

        for(int i=2; i<=10; i++) p1->push_back(i);
        cout << "adding values 2-10...size() = " << p1->size() << endl;

    	cout << "for(int num : *p1):\n";
        for(int num : *p1)
        	cout << num << ' ';
        cout << endl;

        vector<int>* vect = p1.release();
        cout << "vector<int> vect = p1.release()...vect->size() = " 
        	<< vect->size() << endl;

        if(!p1) cout << "p1 == nullptr\n";
        else cerr << "error: p1 is not nullptr\n";
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
