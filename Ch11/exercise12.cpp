/*
    exercise12.cpp

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
        if(!ifs) error("Can't open file ", IN_FILE);
        string text = "";
        char ch;

        while(ifs.get(ch)){
        	text.push_back(ch);
        }

        ofstream ofs{OUT_FILE};
        if(!ofs) error("Can't open file ", OUT_FILE);

        for(int i = text.size()-1; i>=0; i--)
        	ofs << text[i];
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