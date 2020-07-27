/*
    exercise3.cpp

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

        Simple_window win{tl, WIDTH, HEIGHT, "Exercise 3"};

        Open_polyline r;
        r.add(Point{100,300});
        r.add(Point{100,150});
        r.add(Point{200,150});
        r.add(Point{200,225});
        r.add(Point{100,225});
        r.add(Point{200,300});

        r.set_style(Line_style(Line_style::solid, 4));
        r.set_color(Color::red);

        Open_polyline c;
        c.add(Point{350,275});
        c.add(Point{350,300});
        c.add(Point{250,300});
        c.add(Point{250,150});
        c.add(Point{350,150});
        c.add(Point{350,175});

        c.set_style(Line_style(Line_style::solid, 4));
        c.set_color(Color::cyan);

        win.attach(r);
        win.attach(c);

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