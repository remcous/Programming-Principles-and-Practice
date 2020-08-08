/*
    linked_list.cpp

    Revision History:
*/

#include "../std_lib_facilities.h"

/****************************************
*           CLASS DEFINITIONS
****************************************/

class Link{
public:
	string value;

	Link(const string& v, Link* p = nullptr, Link* s = nullptr)
		:value{v}, prev{p}, succ{s}{}

	Link* insert(Link* n);	// insert n before this object
	Link* add(Link* n);		// insert n after this object
	Link* erase();			// remove this object from list
	Link* find(const string& s);	// find s in list
	const Link* find(const string& s) const;	// find s in const list

	Link* advance(int n) const;	// move n positions in list

	Link* next() const{return succ;}
	Link* previous() const{return prev;}
private:
	Link* prev;
	Link* succ;
};

/****************************************
*           FUNCTION PROTOTYPES
****************************************/

void print_all(Link* p);

/****************************************
*           GLOBAL VARIABLES
****************************************/

/****************************************
*             MAIN FUNCTION
****************************************/

int main(){
    try{
        Link* norse_gods = new Link("Thor");
        norse_gods = norse_gods->insert(new Link{"Odin"});
        norse_gods = norse_gods->insert(new Link{"Zeus"});
        norse_gods = norse_gods->insert(new Link{"Freia"});

        Link* greek_gods = new Link("Hera");
        greek_gods = greek_gods->insert(new Link{"Athena"});
        greek_gods = greek_gods->insert(new Link{"Mars"});
        greek_gods = greek_gods->insert(new Link{"Poseidon"});
		
        Link* p = greek_gods->find("Mars");
        if(p) p->value = "Ares";
        /*
        Link* p2 = norse_gods->find("Zeus");
        if(p2){
        	if(p2==norse_gods) norse_gods = p2->next();
        	p2->erase();
        	greek_gods = greek_gods->insert(p2);
        }
        /*
        print_all(norse_gods);
        cout << "\n";

        print_all(greek_gods);
        cout << "\n";*/
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

Link* Link::insert(Link* n)	// insert n before p; return n
{
	if(n == nullptr) return this;	// nothing to insert
	if(this == nullptr) return n;	// nothing to insert into
	n->succ = this;		// this object comes after n
	if(prev) prev->succ = n;	// n comes after what used to be this object's predecessor
	n->prev = prev;	// this object's predecessor becomes n's predecessor
	prev = n;		// n becomes this object's predecessor
	return n;
}

Link* Link::add(Link* n){	// insert n after p; return n
	if(n == nullptr) return this;
	if(this == nullptr) return n;
	n->prev = this;		// p comes before n
	if(succ) succ->prev = n;	// n comes before what used to be p's successor
	n->succ = succ;	// p's successor becomes n's successor
	succ = n;		// n becomes p's successor
	return n;
}

Link* Link::erase(){	// remove *p from list; return p's successor
	Link* p = this;
	if(this == nullptr)	return nullptr;
	if(succ) succ->prev = prev;
	if(prev) prev->succ = succ;
	return succ;
}

const Link* Link::find(const string& s) const{	// find s in list;
									// return nullptr for "not found"
	/*const Link* p = this;
	while(p){
		if(p->value == s) return p;
		p = p->succ;
	}*/
	return nullptr;
}
/*
Link* Link::advance(int n) const{// move n positions in list
							// return nullptr for "not found"
	// positive n moves forward, negative moves backward
	const Link* p = this;
	if(p == nullptr) return nullptr;
	if(n>0){
		while(n--){
			if(p->succ == nullptr) return nullptr;
			p = p->succ;
		}
	}
	else if(n<0){
		while(n++){
			if(p->prev == nullptr) return nullptr;
			p = p->prev;
		}
	}
	return p;
}
*/
void print_all(Link* p){
	cout << "{ ";
	while(p){
		cout << p->value;
		if(p = p->next()) cout << ", ";
	}
	cout << " }";
}

