/*
    list.cpp

    Revision History:
*/

#include <iostream>
using namespace std;

/****************************************
*           CLASS DEFINITIONS
****************************************/

template <typename Elem>
struct Link{
public:
	Link():prev{nullptr}, succ{nullptr}, val{}{}
	Link(const Elem& v):prev{nullptr}, succ{nullptr}, val{v}{}

	~Link(){}

	Link* prev;		// previous link
	Link* succ;		// successor (next) link
	Elem val;		// the value
};

template <typename Elem> class list{
public:
	list(){}

	~list(){
		Link<Elem>* temp = first;
		while(first != nullptr)
		{
			if(first->succ != nullptr)
				first->succ->prev = nullptr;
			temp = first->succ;
			delete first;
			first = temp;
		}
	}

	class iterator;					// member type: iterator

	iterator begin(){return iterator{first};}
	iterator end(){return ++iterator{last};}

	iterator insert(iterator p, const Elem& v);	// insert v into list after p
	iterator erase(iterator p);		// remove p from list

	void push_back(const Elem& v);	// insert v at end
	void push_front(const Elem& v);	// insert v at front
	void pop_front();				// remove the first element
	void pop_back();				// remove the last element

	Elem& front(){return first;}
	Elem& back(){return last;}

	//...
private:
	Link<Elem>* first = nullptr;
	Link<Elem>* last = nullptr;
};

template <typename Elem>	// requries Element<Elem>()
class list<Elem>::iterator{
public:
	iterator(Link<Elem>* p):curr{p}{}

	iterator& operator++(){curr = curr->succ; return *this;}	// pre forward
	iterator& operator--(){curr = curr->prev; return *this;}	// pre backward
	iterator operator++(int){auto temp = curr; curr = curr->succ; return temp;}	// post forward
	iterator operator--(int){auto temp = curr; curr = curr->prev; return temp;}	// post backward
	Elem& operator*(){return curr->val;}	// get value (dereference)

	Link<Elem>* operator->() const{return curr;}
	bool operator==(const iterator& b) const{return curr==b.curr;}
	bool operator!=(const iterator& b) const{return curr!=b.curr;}
private:
	Link<Elem>* curr;		// current link
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
        list<double> d_list;
        d_list.begin();
        d_list.push_back(3.14159);
        d_list.push_back(2.716);
        d_list.push_front(4.43);
        
        list<double>::iterator iter = d_list.begin();
        
        for(; iter != nullptr; iter++)
        	cout << *iter << endl;

        iter = d_list.begin()++;

        d_list.insert(iter, 2.4352);

        cout << "\n.insert()\n";

        for(; iter != nullptr; iter++)
        	cout << *iter << endl;

        d_list.erase(iter);

        cout << "\n.erase()\n";

        for(; iter != nullptr; iter++)
        	cout << *iter << endl;

        cout << "\n.pop_back()\n";
        d_list.pop_back();

        for(iter = d_list.begin(); iter != nullptr; iter++)
        	cout << *iter << endl;
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
*       FUNCTION DEFINITIONS - list
****************************************/

template<typename Elem> 
void list<Elem>::push_back(const Elem& v)
{
	Link<Elem>* temp = new Link<Elem>{v};
	if(first == nullptr && last == nullptr)
	{
		first = temp;
		last = temp;
	}
	else{
		temp->prev = last;
		last->succ = temp;
		last = temp;
	}
}

template<typename Elem> 
void list<Elem>::push_front(const Elem& v)
{
	Link<Elem>* temp = new Link<Elem>{v};
	if(first == nullptr && last == nullptr)
	{
		first = temp;
		last = temp;
	}
	else{
		temp->succ = first;
		first->prev = temp;
		first = temp;
	}
}

template<typename Elem> 
void list<Elem>::pop_front()
{
	Link<Elem>* temp = first;
	first = first->succ;
	first->prev = nullptr;
	delete temp;
}

template<typename Elem> 
void list<Elem>::pop_back()
{
	Link<Elem>* temp = last;
	last = last->prev;
	last->succ = nullptr;
	delete temp;
}

template<typename Elem> 
typename list<Elem>::iterator 
list<Elem>::insert(iterator p, const Elem& v)
{
	Link<Elem>* temp = new Link<Elem>{v};

	temp->succ = p->succ;
	temp->prev = temp->succ->prev;
	temp->prev->succ = temp;

	if(temp->succ != nullptr){
		temp->succ->prev = temp;
	}

	return iterator{temp};
}

template<typename Elem> 
typename list<Elem>::iterator 
list<Elem>::erase(iterator p)
{
	iterator temp = p;

	// p is not the first or last element
	if(p->succ != nullptr && p->prev != nullptr)
	{
		temp--;	// p is a middle element move down one
		p->succ->prev = p->prev;
		p->prev->succ = p->succ;
	}
	else if(p->succ == nullptr)	// p is last element
	{
		temp--;	// p was last element, move down one
		last = p->prev;
		p->prev->succ = nullptr;
	}
	else if(p->prev == nullptr)	// p is first element
	{
		temp++;	// p was first element, move up one
		first = p->succ;
		p->succ->prev = nullptr;
	}
	else iterator temp{nullptr};

	return temp;
}
