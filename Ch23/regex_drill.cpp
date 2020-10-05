/*
    regex_drill.cpp

    Revision History:
*/

#include <regex>
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

/****************************************
*           CLASS DEFINITIONS
****************************************/

/****************************************
*           FUNCTION PROTOTYPES
****************************************/

/****************************************
*           GLOBAL VARIABLES
****************************************/

/****************************************
*             MAIN FUNCTION
****************************************/

int main(){
    ifstream in{"file.txt"};	// input file
    if(!in) cerr << "no file\n";

    regex pat {R"(\w{2}\s*\d{5}(–\d{4})?)"};	// postal code pattern

    int lineno = 0;
    for(string line; getline(in, line);){	// read input into input buffer
    	++lineno;
    	smatch matches;		// matched strings go here
    	if(regex_search(line, matches, pat)){
    		cout << lineno << ": " << matches[0] << '\n';	// whole match
    		if(1<matches.size() && matches[1].matched)
    			cout << "\t: " << matches[1] << '\n';	// sub-match
    	}
    }

    return 0;
}

/****************************************
*       FUNCTION DEFINITIONS - GLOBAL
****************************************/