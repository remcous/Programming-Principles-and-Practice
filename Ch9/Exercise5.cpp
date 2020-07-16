/******************************************************
*	Exercise 5: design and implement a Book class
*	By: Remi Coussement
*	Rev:
*		Exercise 6 - operator support for ==, !=, <<
*		Exercise 5 - Book holds ISBN, title, author, 
*			copyright date - July 2020
******************************************************/
#include "../std_lib_facilities.h"

/**********************************
*		  CLASS DEFINITION
**********************************/

class Book{
public:
	Book();
	Book(string isbn, string title, string author, int copyright, bool checked_out);
	string get_isbn() const{return isbn;}
	string get_title() const{return title;}
	string get_author() const{return author;}
	int get_copyright() const{return copyright;}
	bool get_checked_out() const{return checked_out;}
private:
	bool valid_isbn(string test_isbn) const;
	string isbn;
	string title;
	string author;
	int copyright;
	bool checked_out;
};

/**********************************
*		  FUNCTION PROTOTYPE
**********************************/

bool operator==(const Book& a, const Book& b);
bool operator!=(const Book& a, const Book& b);
ostream& operator<<(ostream& os, const Book& book);

/**********************************
*			MAIN PROGRAM
**********************************/

int main(){
	try{
		Book book1{};
		Book book2{"0-321-99278-4","Programming Principles and Practices using C++ 2e", "Bjarne Stroustrup", 2014, true};
		Book book3{};
		
		
		// test ==
		cout << "TESTING == OPERATOR:\n";
		if(book1 == book2){
			cerr << "Book and 2 shouldn't match but do\n";
		}else cout << "Book 1 and 2 are not the same!\n";
		
		if(book1 == book3){
			cout << "Book 1 and 3 are the same!\n";
		}else cerr << "Book 1 and 3 should match but don't\n";
		
		// test !=
		cout << "\n\nTESTING != OPERATOR:\n";
		if(book1 != book2){
			cout << "Book 1 and 2 are not the same!\n";
		}else cerr << "Book and 2 shouldn't match but do\n";

		if(book1 != book3){
			cerr << "Book 1 and 3 should match but don't\n";
		}else cout << "Book 1 and 3 are the same!\n";
		
		cout << "\n\nTESTING << OPERATOR:\n";
		cout << book2;
		
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

bool Book::valid_isbn(string test_isbn) const{
	// test for valid ISBN
	int count = 0;
	bool previous_digit = false;

	for(int i=0; i<test_isbn.length(); i++){
		if(previous_digit){
			if(isdigit(test_isbn[i])) continue;
			previous_digit = false;
			if(test_isbn[i] != '-') return false;
		}else{
			if(count == 3 && (isalpha(test_isbn[i] || isdigit(test_isbn[i]))))
				count++;
			else if(isdigit(test_isbn[i])){
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

bool operator==(const Book& a, const Book& b){
	int num = a.get_isbn().compare(b.get_isbn());
	return num == 0 ? true : false;
}

bool operator!=(const Book& a, const Book& b){
	return !(a == b);
}


ostream& operator<<(ostream& os, const Book& book){
	os << "Title: " << book.get_title()
		<< "\nAuthor: " << book.get_author()
		<< "\nISBN: " << book.get_isbn() << endl;
	return os;
}