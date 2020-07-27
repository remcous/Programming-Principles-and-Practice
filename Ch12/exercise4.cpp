/*
    exercise4.cpp

    Revision History:
*/

#include "../std_lib_facilities.h"
#include "Simple_window.h"
#include "Graph.h"

/****************************************
*           GLOBAL VARIABLES
****************************************/

#define WIDTH 200
#define HEIGHT 200

/****************************************
*             MAIN FUNCTION
****************************************/

int main(){
    try{
        Point tl{100,100};

        Simple_window win{tl, WIDTH, HEIGHT, "Exercise 4"};

        Rectangle r1{Point{0,0}, WIDTH/3, HEIGHT/3};
        Rectangle r2{Point{WIDTH/3,0}, WIDTH/3, HEIGHT/3};
        Rectangle r3{Point{2*WIDTH/3,0}, WIDTH/3, HEIGHT/3};
        Rectangle r4{Point{0,HEIGHT/3}, WIDTH/3, HEIGHT/3};
        Rectangle r5{Point{WIDTH/3,HEIGHT/3}, WIDTH/3, HEIGHT/3};
        Rectangle r6{Point{2*WIDTH/3,HEIGHT/3}, WIDTH/3, HEIGHT/3};
        Rectangle r7{Point{0,2*HEIGHT/3}, WIDTH/3, HEIGHT/3};
        Rectangle r8{Point{WIDTH/3,2*HEIGHT/3}, WIDTH/3, HEIGHT/3};
        Rectangle r9{Point{2*WIDTH/3,2*HEIGHT/3}, WIDTH/3, HEIGHT/3};

        r1.set_style(Line_style(Line_style::solid, 4));
        r1.set_fill_color(Color::red);
        win.attach(r1);
        r2.set_style(Line_style(Line_style::solid, 4));
        r2.set_fill_color(Color::white);
        win.attach(r2);
        r3.set_style(Line_style(Line_style::solid, 4));
        r3.set_fill_color(Color::red);
        win.attach(r3);
        r4.set_style(Line_style(Line_style::solid, 4));
        r4.set_fill_color(Color::white);
        win.attach(r4);
        r5.set_style(Line_style(Line_style::solid, 4));
        r5.set_fill_color(Color::red);
        win.attach(r5);
        r6.set_style(Line_style(Line_style::solid, 4));
        r6.set_fill_color(Color::white);
        win.attach(r6);
        r7.set_style(Line_style(Line_style::solid, 4));
        r7.set_fill_color(Color::red);
        win.attach(r7);
        r8.set_style(Line_style(Line_style::solid, 4));
        r8.set_fill_color(Color::white);
        win.attach(r8);
        r9.set_style(Line_style(Line_style::solid, 4));
        r9.set_fill_color(Color::red);
        win.attach(r9);

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