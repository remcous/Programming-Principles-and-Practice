/*
    exercise1.cpp

    Revision History:
*/

#include "../std_lib_facilities.h"
#include "Simple_window.h"
#include "Graph.h"

/****************************************
*           CLASS DEFINITIONS
****************************************/

class Smiley: public Circle{
public:
    Smiley(Point c, int rr)
        :Circle{c, rr}{}

    void draw_lines() const;
};

class Frowny: public Circle{
public:
    Frowny(Point c, int rr)
        :Circle{c, rr}{}

    void draw_lines() const;
};

class Hat_smile : public Smiley{
public:
    Hat_smile(Point c, int rr)
        :Smiley{c,rr}{}

    void draw_lines() const;
};

class Hat_frown : public Frowny{
public:
    Hat_frown(Point c, int rr)
        :Frowny{c,rr}{}

    void draw_lines() const;
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

        Smiley smile{Point{WIDTH/4, HEIGHT/4}, WIDTH/4};
        smile.set_fill_color(Color::yellow);
        smile.set_color(Color::black);
        smile.set_style(Line_style(Line_style::solid, 4));

        Frowny frown{Point{3*WIDTH/4, HEIGHT/4}, WIDTH/4};
        frown.set_fill_color(Color::blue);
        frown.set_color(Color::dark_magenta);
        frown.set_style(Line_style(Line_style::solid, 4));

        win.attach(smile);
        win.attach(frown);

        Hat_smile hs{Point{WIDTH/4, 3*HEIGHT/4}, WIDTH/4};
        hs.set_fill_color(Color::yellow);
        hs.set_color(Color::black);
        hs.set_style(Line_style(Line_style::solid, 4));

        Hat_frown hf{Point{WIDTH*3/4, HEIGHT*3/4}, WIDTH/4};
        hf.set_fill_color(Color::cyan);
        hf.set_color(Color::magenta);
        hf.set_style(Line_style(Line_style::dot,8));

        win.attach(hs);
        win.attach(hf);

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

void Smiley::draw_lines() const{
    int start_circle = 0, end_circle = 360; // circle angles
    int start_smile = 240, end_smile = 300; // smile angles

    if (fill_color().visibility()) {    // fill
        fl_color(fill_color().as_int());
        fl_pie(point(0).x,point(0).y, radius()*2, radius()*2, start_circle, end_circle);
        fl_color(color().as_int()); // reset color
    }

    if (color().visibility()) {
        fl_color(color().as_int());
        fl_arc(point(0).x, point(0).y, radius()*2, radius()*2, start_circle, end_circle);
        fl_arc(point(0).x+radius()/2, point(0).y+3*radius()/4, radius()/4, radius()/3, start_circle, end_circle);
        fl_arc(point(0).x+5*radius()/4, point(0).y+radius()*3/4, radius()/4, radius()/3, start_circle, end_circle);
        fl_pie(point(0).x+radius()/2, point(0).y+radius()*3/4, radius()/4, radius()/3, start_circle, end_circle);
        fl_pie(point(0).x+5*radius()/4, point(0).y+radius()*3/4, radius()/4, radius()/3, start_circle, end_circle);
        fl_arc(point(0).x+radius()/2, point(0).y+radius()/2, radius(), radius(), start_smile, end_smile);
    }
}

void Frowny::draw_lines() const{
    int start_circle = 0, end_circle = 360; // circle angles
    int start_frown = 60, end_frown = 120;  // frown angles

    if (fill_color().visibility()) {    // fill
        fl_color(fill_color().as_int());
        fl_pie(point(0).x,point(0).y, radius()*2, radius()*2, start_circle, end_circle);
        fl_color(color().as_int()); // reset color
    }

    if (color().visibility()) {
        fl_color(color().as_int());
        fl_arc(point(0).x, point(0).y, radius()*2, radius()*2, start_circle, end_circle);
        fl_arc(point(0).x+radius()/2, point(0).y+3*radius()/4, radius()/4, radius()/3, start_circle, end_circle);
        fl_arc(point(0).x+5*radius()/4, point(0).y+radius()*3/4, radius()/4, radius()/3, start_circle, end_circle);
        fl_pie(point(0).x+radius()/2, point(0).y+radius()*3/4, radius()/4, radius()/3, start_circle, end_circle);
        fl_pie(point(0).x+5*radius()/4, point(0).y+radius()*3/4, radius()/4, radius()/3, start_circle, end_circle);
        fl_arc(point(0).x+radius()/2, point(0).y+3*radius()/2, radius(), radius(), start_frown, end_frown);
    }
}

void Hat_smile::draw_lines() const{
    Smiley::draw_lines();

    if (fill_color().visibility()) {    // fill
        fl_color(color().as_int());
        fl_pie(point(0).x,point(0).y+radius()/4, radius()*2, radius()/2, 0, 180);
        fl_pie(point(0).x+radius()/4,point(0).y, radius()*1.5, radius()*3/4, 0, 180);
    }

    if (color().visibility()) {
        fl_color(color().as_int());
        fl_arc(point(0).x,point(0).y+radius()/4, radius()*2, radius()/2, 0, 180);
        fl_arc(point(0).x+radius()/4,point(0).y, radius()*1.5, radius()*3/4, 0, 180);
        fl_line(point(0).x, point(0).y+radius()/2, point(0).x+2*radius(), point(0).y+radius()/2);
    }
}

void Hat_frown::draw_lines() const{
    Frowny::draw_lines();

    if (fill_color().visibility()) {    // fill
        fl_color(color().as_int());
        fl_pie(point(0).x,point(0).y+radius()/4, radius()*2, radius()/2, 0, 180);
        fl_pie(point(0).x+radius()/4,point(0).y, radius()*1.5, radius()*3/4, 0, 180);
    }

    if (color().visibility()) {
        fl_color(color().as_int());
        fl_arc(point(0).x,point(0).y+radius()/4, radius()*2, radius()/2, 0, 180);
        fl_arc(point(0).x+radius()/4,point(0).y, radius()*1.5, radius()*3/4, 0, 180);
        fl_line(point(0).x, point(0).y+radius()/2, point(0).x+2*radius(), point(0).y+radius()/2);
    }
}