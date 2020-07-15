// file Chrono.h

namespace Chrono{

enum class Day{
	sunday, monday, tuesday, wednesday, thursday, friday, saturday
};

enum class Month{
	jan=1,feb,mar,apr,may,jun,jul,aug,sep,oct,nov,dec
};

class Date{
public:
	class Invalid{};	// to throw as exception

	Date(int y, Month m, int d);	// check for valid date and initialize
	Date();				// Default constructor
	// the default copy operations are fine

	// non modifying operations:
	int day() const{return d;}
	Month month() const{return m;}
	int year() const{return y;}

	// modifying operations:
	void add_day(int n);
	void add_month(int n);
	void add_year(int n);
private:
	int y;
	Month m;
	int d;
};

bool is_date(int y, Month m, int d);	// true for valid date
bool leapyear(int y);	// true if y is a leap year

bool operator==(const Date& a, const Date& b);
bool operator!=(const Date& a, const Date& b);

ostream& operator<<(ostream& os, const Date& d);
istream& operator>>(istream& is, Date& dd);

Day day_of_week(const Date& d);		// day of week of d
Date next_Sunday(const Date d);		// next Sunday after d
Date next_weekday(const Date& d);	// next weekday after d
}	// Chrono