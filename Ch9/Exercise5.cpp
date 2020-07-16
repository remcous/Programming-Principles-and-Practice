/******************************************************
*	Exercise 5: design and implement a Book class
*	By: Remi Coussement
*	Rev:
*		Exercise 5 - Book holds ISBN, title, author, 
			copyright date - July 2020
******************************************************/
#include "../std_lib_facilities.h"

/**********************************
*		  CLASS DEFINITION
**********************************/

class Book{
public:
	Book();
	Book(string isbn, string title, string author, int copyright, bool checked_out);
	string get_isbn(){return isbn;}
	string get_title(){return title;}
	string get_author(){return author;}
	int get_copyright(){return copyright;}
	bool get_checked_out(){return checked_out;}
private:
	bool valid_isbn(string isbn);
	string isbn;
	string title;
	string author;
	int copyright;
	bool checked_out;
};

/**********************************
*		  FUNCTION PROTOTYPE
**********************************/

/**********************************
*			MAIN PROGRAM
**********************************/

int main(){
	try{
		string isbn;
		cout << "Enter ISBN: ";
		cin >> isbn;
		Book(isbn, "PPP", "Bjarne Stroustrup", 2014, false);

		return 0;
	}catch(exception& e){
		cerr << "Error: " << e.what() << "\n";
		return 1;
	}catch(...){
		cerr << "Oops: Unknown exception\n";
		return 2;
	}
}

/**********************************
*		   MEMBER FUNCTIONS
**********************************/

Book::Book(){
	isbn = "0-00000-000-x";
	title = "";
	author = "";
	copyright = 1970;
	checked_out = false;
}

Book::Book(string isbn, string title, string author, int copyright, bool checked_out){
	if(!valid_isbn(isbn)) error("Invalid ISBN format");

	this->isbn = isbn;
	this->title = title;
	this->author = author;
	this->copyright = copyright;
	this->checked_out = checked_out;
}

bool Book::valid_isbn(string isbn){
	// test for valid ISBN
	int count = 0;
	bool previous_digit = false;

	for(int i=0; i<isbn.length(); i++){
		if(previous_digit){
			if(isdigit(isbn[i])) continue;
			previous_digit = false;
			if(isbn[i] != '-') return false;
		}else{
			if(count == 3 && (isalpha(isbn[i] || isdigit(isbn[i]))))
				count++;
			else if(isdigit(isbn[i])){
				count++;
				previous_digit = true;
			}else return false;
		}
	}

	if(count != 4) return false;
	return true;
}

/**********************************
*		   GLOBAL FUNCTIONS
**********************************/
