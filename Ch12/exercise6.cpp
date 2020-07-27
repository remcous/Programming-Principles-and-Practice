/*
    exercise6.cpp

    Revision History:
*/

#include "../std_lib_facilities.h"
#include "Simple_window.h"
#include "Graph.h"

/****************************************
*           GLOBAL VARIABLES
****************************************/

// laptop resolution is 1440*900
#define WIDTH 1920
#define HEIGHT 1080

/****************************************
*             MAIN FUNCTION
****************************************/

int main(){
    try{
        Point tl{100,100};

        Simple_window win{tl, WIDTH, HEIGHT, "Exercise 6"};

        win.wait_for_button();
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