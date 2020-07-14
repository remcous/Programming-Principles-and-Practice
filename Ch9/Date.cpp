#include "../std_lib_facilities.h"

/***********************************************
*			CLASS/STRUCT DEFINITIONS
***********************************************/

// Simple Date (some people prefer implementation details last)
class Date{
public:
	class Invalid{};			// to be used as exception
	Date(int y, int m, int d);	// check for valid date and initialize
	void add_day(int n);		// increase the Date by n days
	int month(){return m;}
	int day(){return d;}
	int year(){return y;}
private:
	int y,m,d;			// year, month, day
	bool is_valid();	// return true if date is valid
};

enum class Month{
	jan=1,feb,mar,apr,may,jun,jul,aug,sep,oct,nov,dec
};

enum class Day{
	monday,tuesday,wednesday,thursday,friday,saturday,sunday
};

/***********************************************
*				GLOBAL VARIABLES
***********************************************/

vector<string> month_tbl = {
	"", "January", "February", "March", "April", 
	"May", "June", "July", "August", "September",
	"October", "November", "December"
};

/***********************************************
*				FUNCTION PROTOTYPES
***********************************************/

Month int_to_month(int x);
Month operator++(Month& m);
ostream& operator<<(ostream& os, Month m);

/***********************************************
*				  MAIN PROGRAM
***********************************************/

int main(){
	Month m = Month::sep;

	cout << ++m << endl;
	cout << ++m << endl;
	cout << ++m << endl;
	cout << ++m << endl;

	return 0;
}

/***********************************************
*				GLOBAL FUNCTIONS
***********************************************/

Month int_to_month(int x){
	if(x<int(Month::jan)||int(Month::dec)<x) error("bad month");
	return Month(x);
}

Month operator++(Month& m){
	m = (m==Month::dec) ? Month::jan : Month(int(m)+1);	// wrap around
	return m;
}

ostream& operator<<(ostream& os, Month m){
	return os << month_tbl[int(m)];
}

/***********************************************
*			  DATE MEMBER FUNCTIONS
***********************************************/

Date::Date(int yy, int mm, int dd)	// Constructor
	:y{yy}, m{mm}, d{dd}
{
	if(!is_valid()) throw Invalid{};
}

void Date::add_day(int n){
	//	...
}

bool Date::is_valid(){
	if(m<1||m>12) return false;
	// ...
	return true;
}