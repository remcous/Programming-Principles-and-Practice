/*
    exercise5.cpp

    Revision History:
*/

#include "../std_lib_facilities.h"
#include "Simple_window.h"
#include "Graph.h"

/****************************************
*           GLOBAL VARIABLES
****************************************/

#define PPI 128

/****************************************
*             MAIN FUNCTION
****************************************/

int main(){
    try{
        Point tl{100,100};

        const int width = (x_max()*2/3 + PPI/2);
        const int height = (y_max()*3/4 + PPI/2);

        Simple_window win{tl, width, height, "Exercise 5"};

        Rectangle r{Point{0,0}, width, height};

        r.set_color(Color::red);
        r.set_fill_color(Color::red);

        Rectangle r2{Point{PPI/4,PPI/4}, x_max()*2/3, y_max()*3/4};
        r2.set_fill_color(Color::white);

        win.attach(r);
        win.attach(r2);

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