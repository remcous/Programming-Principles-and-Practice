/*
    exercise4.cpp

	Takes input integers in decimal, octal, and hex formats and
	output them formatted in a table into decimal

    Revision History:
*/

#include "../std_lib_facilities.h"

/****************************************
*           CLASS DEFINITIONS
****************************************/

enum class num_format{
	decimal, octal, hexadecimal
};

struct Num{
public:
	Num(int val, num_format nf)
		:value{val}, format{nf} {}
	Num(): value{0}, format{num_format::decimal}{}

	void print_table();
private:
	int value;
	num_format format;
};

/****************************************
*           FUNCTION PROTOTYPES
****************************************/

bool read_num(istream& is, int& value, num_format& nf);

/****************************************
*             MAIN FUNCTION
****************************************/

int main(){
    try{
    	vector<Num> num_list;
    	int val;
    	num_format nf;

    	while(read_num(cin, val, nf)){
    		Num num{val, nf};
    		num_list.push_back(num);
    	}

    	for(Num num : num_list){
    		num.print_table();
    	}
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

bool read_num(istream& is, int& value, num_format& nf){
	char c=' ';
	is.get(c);

	// ignore non-alphanumeric characters, return false on newline
	while(!isalnum(c)){
		if(c=='\n') return false;
		is.get(c);
	}

	// confirm that istream hasn't failed
	if(is.bad() || is.eof()) return false;

	// test for hex, oct, or dec input and handle accordingly
	if(c=='0'){
		is.get(c);
		if(c=='x' || c=='X'){
			nf = num_format::hexadecimal;
			is >> hex >> value;
		}
		if(isdigit(c)){
			is.putback(c);
			nf = num_format::octal;
			is >> oct >> value;
		}
	}else if(isdigit(c)){
		is.putback(c);
		nf = num_format::decimal;
		is >> dec >> value;
	}else return false;

	return true;
}

void Num::print_table(){
	cout << showbase;

	// Handle portion of table that varies by format
	switch(format){
	case num_format::decimal:
		cout << right << setw(4) << dec << value
			<< left << setw(12) << " decimal";
		break;
	case num_format::hexadecimal:
		cout << right << setw(4) << hex << value
			<< left << setw(12) << " hexadecimal";
		break;
	case num_format::octal:
		cout << right << setw(4) << oct << value
			<< left << setw(12) << " octal";
		break;
	default:
		error("Unknown num_format");
	}

	// print out common portion
	cout << " converts to" << right << setw(4) 
		<< dec << value << " decimal\n";
}