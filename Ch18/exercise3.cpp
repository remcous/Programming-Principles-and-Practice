/*
    exercise3.cpp

    Revision History:
*/

#include "../std_lib_facilities.h"

/****************************************
*           CLASS DEFINITIONS
****************************************/

/****************************************
*           FUNCTION PROTOTYPES
****************************************/

// Compare two C strings, return 0 if the strings are identical
// return -ve or +ve respectively if s1 is lexicographically before or after s2
int strcmp(const char* s1, const char* s2);

// Concatenates two strings with a dot '.' in between
string cat_dot(const string& s1, const string& s2);
string cat_dot(const string& s1, const string& s2, const string& sep);
char* cat_dot(const char* s1, const char* s2, const char sep);

/****************************************
*           GLOBAL VARIABLES
****************************************/

/****************************************
*             MAIN FUNCTION
****************************************/

int main(){
    try{
        char s1[] = "Hello";
        char s2[] = "World";

        cout << strcmp(s1, s2) << '\n';

        cout << cat_dot("Niels", "Bohr") << '\n';
        cout << cat_dot("Niels", "Bohr", ":") << '\n';
        
        char* output = cat_dot(s1, s2, ' ');
        cout << output << '\n';

        delete[] output;
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

int strcmp(const char* s1, const char* s2){
	// compare the strings character by character
	int i;

	for(i=0; *(s1+i) != 0 && *(s2+i) != 0; i++)
	{
		static char temp1, temp2;
		if( *(s1+i) == *(s2+i)) continue;	// characters are the same

		if(*(s1+i) >= 'A' && *(s1+i) <= 'Z') temp1 = *(s1+i) - ('A' - 'a');
		else temp1 = *(s1+i);

		if(*(s2+i) >= 'A' && *(s2+i) <= 'Z') temp2 = *(s2+i) - ('A' - 'a');
		else temp2 = *(s2+i);

		if(temp2 != temp1) return temp1 - temp2;
	}

	if( *(s1+i) == 0 && *(s2+i) != 0) return -1;
	else if( *(s1+1) != 0 && *(s2+i) == 0) return 1;

	return 0;
}

string cat_dot(const string& s1, const string& s2){
	return s1 + "." + s2;
}

string cat_dot(const string& s1, const string& s2, const string& sep){
	return s1 + sep + s2;
}

char* cat_dot(const char* s1, const char* s2, const char sep){
	int length = 1;	// seperator is a single char

	for(int i=0; *(s1+i)!=0; i++) length++;
	for(int i=0; *(s2+i)!=0; i++) length++;

	char *result = new char[length+1];
	
	int i = 0;
	for(int j=0; *(s1+j)!=0; j++){
		result[i] = *(s1+j);
		i++;
	}

	result[i] = sep;
	i++;

	for(int j=0; *(s2+j)!=0; j++){
		result[i] = *(s2+j);
		i++;
	}

	result[length] = 0;

	return result;
}
