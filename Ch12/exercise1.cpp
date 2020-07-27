/*
    exercise1.cpp

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

        Simple_window win{tl, WIDTH, HEIGHT, "Exercise 1"};

        Rectangle r{Point{100,100}, 150, 50};

        Polygon poly;
        poly.add(Point{300, 200});
        poly.add(Point{350, 200});
        poly.add(Point{350, 100});
        poly.add(Point{300, 100});

        r.set_color(Color::blue);
        poly.set_color(Color::red);

        win.attach(r);
        win.attach(poly);

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