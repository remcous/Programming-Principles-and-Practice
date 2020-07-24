/*
    exercise3.cpp

	Input the text from a file, parse the lines and remove all vowels
	and output the result to the console

    Revision History:
*/

#include "../std_lib_facilities.h"

/****************************************
*           FUNCTION PROTOTYPES
****************************************/

void remove_vowels(string& s);

/****************************************
*           GLOBAL VARIABLES
****************************************/

#define IN_FILE "input.txt"
#define VOWELS "aeiouAEIOU"

/****************************************
*             MAIN FUNCTION
****************************************/

int main(){
    try{
        ifstream ifs{IN_FILE};
        string line;

        while(getline(ifs, line)){
        	remove_vowels(line);
        	cout << line << '\n';
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

void remove_vowels(string& s){
	string disemvoweled = "";
	bool is_vowel;

	for(char ch : s){
		is_vowel = false;
		for(char vowel : VOWELS){
			if(ch == vowel){
				is_vowel = true;
				break;
			}
		}

		if(!is_vowel) disemvoweled += ch;
	}

	s = disemvoweled;
}