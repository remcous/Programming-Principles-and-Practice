/*
    exercise14.cpp

    Revision History:
*/

#include "../Libraries/std_lib_facilities.h"

/****************************************
*           CLASS DEFINITIONS
****************************************/

template <typename Elem>
struct Link{
public:
	Link(): succ{nullptr}, val{}{}
	Link(const Elem& v): succ{nullptr}, val{v}{}

	~Link(){}

	Link* succ;		// successor (next) link
	Elem val;		// the value
};

// FIFO list
template <typename T>
class slist{
public:
	using value_type = T;
	using size_type = unsigned long;

	class iterator;

	slist():data{nullptr}, last{nullptr}{}
	~slist(){
		while(auto temp = data)
		{
			data = data->succ;
			delete temp;
		}
	}

	iterator begin(){return iterator{data};}
	iterator end(){return iterator{nullptr};}

	void push_back(const T& v);	// insert v at end
	void pop_front();			// remove the first element

	T& front(){return data;}
private:
	Link<value_type>* data;
	Link<value_type>* last;

	T& back(){return last;}
};

template<typename T>
class slist<T>::iterator{
public:
	iterator(Link<T>* p): curr{p}{}

	// pre and post increment operators
	iterator& operator++(){curr = curr->succ; return *this;}
	iterator operator++(int){auto temp=curr; curr = curr->succ; return temp;}

	// dereference operator
	T& operator*(){return curr->val;}

	bool operator==(const iterator& b){return curr == b.curr;}
	bool operator!=(const iterator& b){return curr != b.curr;}
private:
	Link<T>* curr;
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
    	cout << "Creating fifo object...\n";
        slist<int> fifo;
        cout << "fifo created\n";

        cout << "Adding elements 0,1,2...,9\n";
        for(int i=0; i<10; i++)
        	fifo.push_back(i);

        cout << "Confirm using iterator for loop...\n";
        
        for(auto i=fifo.begin(); i != fifo.end(); i++)
        {
        	cout << *i << ' ';
        }

        cout << "\nDone.\n"
        	<< "Pop two elements off the front...\n";

        fifo.pop_front();
        fifo.pop_front();

        cout << "Confirm using iterator for loop...\n";

        for(auto i=fifo.begin(); i != fifo.end(); i++)
        {
        	cout << *i << ' ';
        }

        cout << "\nDone.\n";
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
*       FUNCTION DEFINITIONS - GLOBAL
****************************************/

template <typename T>
void slist<T>::push_back(const T& v)
{
	Link<T>* temp = new Link<T>{v};

	if(data == nullptr)
		data = temp;

	if(last != nullptr)
		last->succ = temp;
	
	last = temp;
}

template <typename T>
void slist<T>::pop_front()
{
	if(data == nullptr) return;

	auto temp = data;
	data = data-> succ;
	delete temp;
}
