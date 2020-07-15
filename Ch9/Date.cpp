#include "../std_lib_facilities.h"

/***********************************************
*			CLASS/STRUCT DEFINITIONS
***********************************************/

enum class Month{
	jan=1,feb,mar,apr,may,jun,jul,aug,sep,oct,nov,dec
};

enum class Day{
	monday,tuesday,wednesday,thursday,friday,saturday,sunday
};

// Simple Date (some people prefer implementation details last)
class Date{
public:
	// ...
	Month month() const{return m;}	// const member: can't modify the object
	int day() const{return d;}	// const member: can't modify the object
	int year() const{return y;}	// const member: can't modify the object

	class Invalid{};			// to be used as exception
	Date(int y, Month m, int d);	// check for valid date and initialize
	void add_day(int n);		// increase the Date by n days
	void add_month(int n);
	void add_year(int n);
	
private:
	int y;				// year
	Month m;
	int d;				// day
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

Date::Date(int yy, Month mm, int dd)	// Constructor
	:y{yy}, m{mm}, d{dd}
{
}

void Date::add_day(int n){
	//	...
}