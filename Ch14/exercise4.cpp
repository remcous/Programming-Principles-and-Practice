/*
    exercise4.cpp

    Revision History:
*/

#include "../std_lib_facilities.h"
#include "Simple_window.h"
#include "Graph.h"

/****************************************
*           CLASS DEFINITIONS
****************************************/

class Immobile_circle : public Circle{
public:
    Immobile_circle(Point c, int rr):Circle{c,rr}{}
private:
    Circle::move;
};

/****************************************
*           GLOBAL VARIABLES
****************************************/

#define WIDTH 400
#define HEIGHT 400

/****************************************
*             MAIN FUNCTION
****************************************/

int main(){
    try{
        Point tl{0,0};

        Simple_window win{tl, WIDTH, HEIGHT, "Chapter 14 - Exercise 1"};

        Immobile_circle ic(Point{WIDTH/2, HEIGHT/2}, WIDTH/4);

        win.attach(ic);

        win.wait_for_button();

        // Won't compile as expected, move is private and inaccessible
        ic.move(WIDTH/4,0);
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

/****************************************
*           FUNCTIONS - CLASSES
****************************************/
