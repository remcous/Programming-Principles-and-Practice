/*
    exercise2.cpp

    Revision History:
*/

#include "../std_lib_facilities.h"
#include "Simple_window.h"
#include "Graph.h"

/****************************************
*           GLOBAL VARIABLES
****************************************/

#define WIDTH 600
#define HEIGHT 400

/****************************************
*             MAIN FUNCTION
****************************************/

int main(){
    try{
        Point tl{100,100};

        Simple_window win{tl, WIDTH, HEIGHT, "Exercise 2"};

        Rectangle r{Point{100,100}, 100, 30};
        Text t{Point{120,120}, "HOWDY!"};

        win.attach(r);
        win.attach(t);

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