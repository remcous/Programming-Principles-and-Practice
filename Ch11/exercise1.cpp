/*
    exercise1.cpp

	Input lines from a file, replace all uppercase with lowercase
	and place the result in a different (potentially) output file

    Revision History:
*/

#include "../std_lib_facilities.h"

/****************************************
*           GLOBAL VARIABLES
****************************************/

#define IN_FILE "input.txt"
#define OUT_FILE "output.txt"

/****************************************
*             MAIN FUNCTION
****************************************/

int main(){
    try{
    	ifstream ifs{IN_FILE};
    	ofstream ofs{OUT_FILE};
        string line;

        while(getline(ifs, line)){
        	for(char& ch : line)
        		ch = tolower(ch);
        	ofs << line << '\n';
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