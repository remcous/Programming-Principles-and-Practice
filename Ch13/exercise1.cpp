/*
    GraphicsClassDrill.cpp

    Revision History:
*/

#include "../std_lib_facilities.h"
#include "Simple_window.h"
#include "Graph.h"
#include <cmath>

/****************************************
*           CLASS DEFINITIONS
****************************************/

struct Arc : Shape{
    // Center, width, height, starting and ending angles
    Arc(Point p, int w, int h, int start, int end)
        : width{w}, height{h}, start_angle{start}, end_angle{end}
    {
        add(Point{p.x-w/2, p.y-h/2});
    }

    void draw_lines() const;

private:
    int width;
    int height;
    int start_angle;
    int end_angle;
};

struct Rounded_box : Shape{
    Rounded_box(Point p, int w, int h, int r)
        : width{w}, height{h}, radius{r}
    {
        if(height < 0 || width < 0) error("Bad rounded rectangle: non-positive side");
        if(2*radius > height || 2*radius > width) error("Bad rounded rectangle: radius too large");
        add(p);
    }
    Rounded_box(Point a, Point b, int r)
        : width{b.x-a.x}, height{b.y-a.y}, radius{r}
    {
        if(height < 0 || width < 0) error("Bad rounded rectangle: non-positive side");
        if(2*radius > height || 2*radius > width) error("Bad rounded rectangle: radius too large");
        add(a);
    }

    void draw_lines() const;

private:
    int width;
    int height;
    int radius;
};

struct Arrow : Shape{
    Arrow(Point a, Point b);

    void draw_lines() const;
};

/****************************************
*           FUNCTION PROTOTYPES
****************************************/

Point nw(Rectangle& r);
Point ne(Rectangle& r);
Point sw(Rectangle& r);
Point se(Rectangle& r);
Point n(Rectangle& r);
Point e(Rectangle& r);
Point s(Rectangle& r);
Point w(Rectangle& r);
Point center(Rectangle& r);

/****************************************
*           GLOBAL VARIABLES
****************************************/

#define WIDTH 1000
#define HEIGHT 800

/****************************************
*             MAIN FUNCTION
****************************************/

int main(){
    try{
        Point tl{0,0};

        Simple_window win{tl, WIDTH, HEIGHT, "Chapter 13 - Graphics Classes Drill"};

        Arc a{Point{400,200},300,100,0,180};
        Arc b{Point{600, 400}, 10, 200, -45, 0};
        Arc c{Point{WIDTH/2, HEIGHT/2}, WIDTH/2, HEIGHT/3, 0, 360};

        c.set_style(Line_style(Line_style::dash, 4));
        c.set_color(Color::red);

        win.attach(a);
        win.attach(b);
        win.attach(c);

        Rounded_box rb(tl, 200, 100, 25);

        win.attach(rb);

        Arrow arrow_line{Point{500,100}, Point{400,200}};

        Arrow arrow_line1{Point{200,700}, Point{300,700}};
        
        Arrow arrow_line2{Point{800,500}, Point{758,232}};

        win.attach(arrow_line);
        win.attach(arrow_line1);        
        win.attach(arrow_line2);

        Rectangle rect{Point{WIDTH/2-100, HEIGHT/2-100}, 200, 200};
        win.attach(rect);

        Mark rect_nw{nw(rect), 'x'};
        Mark rect_ne{ne(rect), 'x'};
        Mark rect_sw{sw(rect), 'x'};
        Mark rect_se{se(rect), 'x'};
        Mark rect_n{n(rect), 'x'};
        Mark rect_e{e(rect), 'x'};
        Mark rect_s{s(rect), 'x'};
        Mark rect_w{w(rect), 'x'};
        Mark rect_center{center(rect), 'x'};

        win.attach(rect_nw);
        win.attach(rect_ne);
        win.attach(rect_sw);
        win.attach(rect_se);
        win.attach(rect_n);
        win.attach(rect_e);
        win.attach(rect_s);
        win.attach(rect_w);
        win.attach(rect_center);

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

void Arc::draw_lines() const{
    if(color().visibility())
        fl_arc(point(0).x, point(0).y, width, height, start_angle, end_angle);
}

void Rounded_box::draw_lines() const{
    fl_arc(point(0).x, point(0).y, 2*radius, 2*radius, 90, 180);
    fl_arc(point(0).x+width-2*radius, point(0).y, 2*radius, 2*radius, 0, 90);
    fl_arc(point(0).x, point(0).y+height-2*radius, 2*radius, 2*radius, 180, 270);
    fl_arc(point(0).x+width-2*radius, point(0).y+height-2*radius, 2*radius, 2*radius, 270, 0);
    fl_line(point(0).x+radius, point(0).y, point(0).x+width-radius, point(0).y);
    fl_line(point(0).x+radius, point(0).y+height, point(0).x+width-radius, point(0).y+height);
    fl_line(point(0).x, point(0).y+radius, point(0).x, point(0).y+height-radius);
    fl_line(point(0).x+width, point(0).y+radius, point(0).x+width, point(0).y+height-radius);
}

Arrow::Arrow(Point a, Point b){
    add(a);
    add(b);

    double x = (b.x - a.x)/sqrt(pow(b.x-a.x, 2) + pow(b.y-a.y, 2));
    double y = (b.y - a.y)/sqrt(pow(b.x-a.x, 2) + pow(b.y-a.y, 2));

    Point c{b.x-10*x+5*y, b.y-10*y-5*x};
    Point d{b.x-10*x-5*y, b.y-10*y+5*x};
    
    add(c);
    add(d);

    set_color(Color::black);
    set_fill_color(Color::black);
}

void Arrow::draw_lines() const{
    fl_line(point(0).x, point(0).y, point(1).x, point(1).y);
    fl_line(point(1).x, point(1).y, point(2).x, point(2).y);
    fl_line(point(2).x, point(2).y, point(3).x, point(3).y);
    fl_line(point(3).x, point(3).y, point(1).x, point(1).y);

    if (fill_color().visibility()) {
        fl_color(fill_color().as_int());
        fl_begin_complex_polygon();
        for(int i=1; i<number_of_points(); ++i){
            fl_vertex(point(i).x, point(i).y);
        }
        fl_end_complex_polygon();
        fl_color(color().as_int()); // reset color
    }
}

Point nw(Rectangle& r){
    return Point{r.point(0).x, r.point(0).y};
}

Point ne(Rectangle& r){
    return Point{r.point(0).x+r.width(), r.point(0).y};
}

Point sw(Rectangle& r){
    return Point{r.point(0).x, r.point(0).y+r.height()};
}

Point se(Rectangle& r){
    return Point{r.point(0).x+r.width(), r.point(0).y+r.height()};
}

Point n(Rectangle& r){
    return Point{r.point(0).x+r.width()/2, r.point(0).y};
}

Point e(Rectangle& r){
    return Point{r.point(0).x+r.width(), r.point(0).y+r.height()/2};
}

Point s(Rectangle& r){
    return Point{r.point(0).x+r.width()/2, r.point(0).y+r.height()};
}

Point w(Rectangle& r){
    return Point{r.point(0).x, r.point(0).y+r.height()/2};
}

Point center(Rectangle& r){
    return Point{r.point(0).x+r.width()/2, r.point(0).y+r.height()/2};
}