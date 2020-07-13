#include "../std_lib_facilities.h"

/***********************************************
*			CLASS/STRUCT DEFINITIONS
***********************************************/

// Simple Date (too simple?)
struct Date{
	int y;	// year
	int m;	// month in year
	int d;	// day of month
};

/***********************************************
*				GLOBAL VARIABLES
***********************************************/

Date today;	// Date variable (a named object)

/***********************************************
*				FUNCTION PROTOTYPES
***********************************************/

void init_day(Date&, int y, int m, int d);
void add_day(Date& dd, int n);
void f();

/***********************************************
*				  MAIN PROGRAM
***********************************************/

int main(){
	return 0;
}

/***********************************************
*				GLOBAL FUNCTIONS
***********************************************/

void init_day(Date& dd, int y, int m, int d){
	// check that (y,m,d) is a valid date
	// if it is use it to initialize dd
}

void add_day(Date& dd, int n){
	// increase dd by n days
}

void f(){
	Date today;
	init_day(today, 12, 24, 2005);
	add_day(today, 1);
}