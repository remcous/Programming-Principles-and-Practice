/*
    exercise2.cpp

	Search for a target word in an input file and
	output the line number and text of any lines
	contatining the target
	
    Revision History:
*/

#include "../std_lib_facilities.h"

/****************************************
*           GLOBAL VARIABLES
****************************************/

#define IN_FILE "input.txt"
#define TARGET "hello"

/****************************************
*             MAIN FUNCTION
****************************************/

int main(){
    try{
        ifstream ifs{IN_FILE};
        string line, target;
        int line_num = 0;

        while(getline(ifs, line)){
        	static istringstream iss;
        	line_num++;
        	iss.str(line);

        	if(iss.fail()) iss.clear();
        	for(string word;iss >> word;){
        		for(char& ch : word)
        			ch = tolower(ch);
        		if(!(word.compare(TARGET))){
        			cout << line_num << ": " << line << '\n';
        			break;
        		}
        	}
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