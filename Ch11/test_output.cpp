#include "../std_lib_facilities.h"

#define LN_LENGTH 10
#define FN_LENGTH 10
#define PHONE_LENGTH 15
#define EMAIL_LENGTH 25

int main(){
	int birth_year = 1992;
	int age = 27;

	cout << "DEC\tHEX\tOCT\n";
	cout << dec << birth_year << '\t'
		<< hex << birth_year  << '\t'
		<< oct << birth_year << endl;

	cout << dec << age << '\t'
		<< hex << age << '\t'
		<< oct << age << endl;

	int a,b,c,d;
	cin >> a >> oct >> b >> hex >> c >> d;
	cout << a << '\t' << b << '\t' << c << '\t' << d << '\n';

	double num = 1234567.89;
	// defaultfloat not supported by g++ 4.9.2 (command line tools for mac)
	cout /*<< std::defaultfloat*/ << num << '\t'
		<< fixed << num << '\t'
		<< scientific << num << '\n';

	cout << '|' << left << setw(LN_LENGTH) << "LAST NAME" << '|' 
		<< setw(FN_LENGTH) << "FIRST NAME" << '|'
		<< setw(PHONE_LENGTH) << "PHONE NUMBER" << '|'
		<< setw(EMAIL_LENGTH) << "EMAIL" << '|' << endl;

	cout <<'+';
	for(int i=0; i<LN_LENGTH; i++) cout << '-';
	cout << '+';
	for(int i=0; i<FN_LENGTH; i++) cout << '-';
	cout << '+';
	for(int i=0; i<PHONE_LENGTH; i++) cout << '-';
	cout << '+';
	for(int i=0; i<EMAIL_LENGTH; i++) cout << '-';
	cout <<'+' << endl;
	
	cout << '|' <<left << setw(LN_LENGTH) << "COUSSEMENT" << '|' 
		<< setw(FN_LENGTH) << "REMI" << '|'
		<< setw(PHONE_LENGTH) << "(905) 123-4567" << '|'
		<< setw(EMAIL_LENGTH) << "remi@email.com" << '|' << endl;
	cout << '|' << left << setw(LN_LENGTH) << "FIGEL" << '|' 
		<< setw(FN_LENGTH) << "MARTIN" << '|'
		<< setw(PHONE_LENGTH) << "(250) 123-4567" << '|'
		<< setw(EMAIL_LENGTH) << "martin@email.com" << '|' << endl;
	cout << '|' << left << setw(LN_LENGTH) << "DOE" << '|' 
		<< setw(FN_LENGTH) << "JOHN" << '|'
		<< setw(PHONE_LENGTH) << "(555) 867-5309" << '|'
		<< setw(EMAIL_LENGTH) << "jenny@email.com" << '|' << endl;
}