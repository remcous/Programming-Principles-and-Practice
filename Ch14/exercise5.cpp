/*
    exercise5.cpp

    Revision History:
        ex5 - create a Striped_rectangle class to fill
            a rectangle shape with equally spaced horizontal lines
        ex6 - create a Striped_circle class similar to Striped_rectangle
        ex7 - create a Striped_closed_polyline class similar to above
*/

#include "../std_lib_facilities.h"
#include "Simple_window.h"
#include "Graph.h"

/****************************************
*           CLASS DEFINITIONS
****************************************/

class Striped_rectangle : public Rectangle{
public:
    Striped_rectangle(Point p, int w, int h)
        :Rectangle{p,w,h}, line_gap{3}{}
    Striped_rectangle(Point a, Point b)
        :Rectangle{a, b}, line_gap{3}{}

    void draw_lines() const;
    void set_line_gap(int lg){line_gap=lg;}
private:
    int line_gap;
};

class Striped_circle : public Circle{
public:
    Striped_circle(Point c, int rr)
        :Circle{c,rr}, line_gap{3}{}

    void draw_lines() const;
    void set_line_gap(int lg){line_gap=lg;}
private:
    int line_gap;
};

class Striped_closed_polyline : public Closed_polyline{
public:
    using Closed_polyline::Closed_polyline;

    void draw_lines() const;
    void set_line_gap(int lg){line_gap=lg;}
private:
    int line_gap{3};
};

/****************************************
*           GLOBAL VARIABLES
****************************************/

bool line_intersect(Point, Point, Point, Point, Point&);

/****************************************
*           GLOBAL VARIABLES
****************************************/

#define WIDTH 800
#define HEIGHT 800

/****************************************
*             MAIN FUNCTION
****************************************/

int main(){
    try{
        Point tl{0,0};

        Simple_window win{tl, WIDTH, HEIGHT, "Chapter 14 - Exercise 5"};

        // EXERCISE 5 - Striped_rectangle
        Striped_rectangle sr{Point{100,100}, 200, 100};
        sr.set_fill_color(Color::white);
        sr.set_style(Line_style::dash);
        sr.set_color(Color::red);

        win.attach(sr);

        // EXERCISE 6 - Striped_circle
        Striped_circle sc{Point{600, 150}, 50};
        sc.set_fill_color(Color::black);
        sc.set_color(Color::white);

        win.attach(sc);

        // TEST FUNCTION line_intersect
        Point a{400,400};
        Point b{600,600};
        Point c{400,600};
        Point d{600,400};

        Line l1{a, b};
        Line l2{c, d};

        win.attach(l1);
        win.attach(l2);

        Point m;
        line_intersect(a,b,c,d,m);
        Mark mark{m, 'o'};
        win.attach(mark);


        // EXERCISE 7 - Striped_closed_polyline test
        Striped_closed_polyline scp;
        scp.add(Point{100,700});
        scp.add(Point{300,600});
        scp.add(Point{250,650});
        scp.add(Point{150,700});
        scp.add(Point{200,600});

        scp.set_color(Color::black);
        scp.set_fill_color(Color::red);

        win.attach(scp);

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

void Striped_rectangle::draw_lines() const{
    Rectangle::draw_lines();

    if (color().visibility()) {
        fl_color(color().as_int()); // reset color
        for(int i = point(0).y-height(); i<point(0).y; i+= line_gap){
            fl_line(point(0).x, point(0).y+i, point(0).x+width(), point(0).y+i);
        }
    }
}

void Striped_circle::draw_lines() const{
    Circle::draw_lines();

    Point c = center();
    int r = radius();
    int w, h;

    if (color().visibility()) {
        fl_color(color().as_int()); // reset color
        fl_line(c.x-r, c.y, c.x+r, c.y);
        for(h=0; h<r; h+=line_gap){
            w = r * cos( asin((double)h/r));
            fl_line(c.x-w, c.y+h, c.x+w, c.y+h);
            fl_line(c.x-w, c.y-h, c.x+w, c.y-h);
        }
    }
}

bool line_intersect(Point a, Point b, Point c, Point d, Point& result){
    int denom = (b.x-a.x)*(d.y-c.y) - (d.x-c.x)*(b.y-a.y);

    if(denom == 0) return false;    // parallel

    result.x = ((b.x*a.y - a.x*b.y)*(d.x-c.x) 
        - (d.x*c.y - c.x*d.y)*(b.x-a.x)) / denom;

    result.y = ((b.x*a.y - a.x*b.y)*(d.y-c.y) 
        - (d.x*c.y - c.x*d.y)*(b.y-a.y)) / denom;

    int x_min, x_max, y_min, y_max;

    x_min = fmax(fmin(a.x, b.x), fmin(c.x, d.x));   // most restrictive
    x_max = fmin(fmax(a.x, b.x), fmax(c.x, d.x));

    y_min = fmax(fmin(a.y, b.y), fmin(c.y, d.y));   // most restrictive
    y_max = fmin(fmax(a.y, b.y), fmax(c.y, d.y));

    if(result.x > x_max || result.x < x_min || result.y > y_max || result.y < y_min)
        return false;   // out of bounds

    return true;
}

void Striped_closed_polyline::draw_lines() const{
    Closed_polyline::draw_lines();
    
    if(color().visibility()){
        fl_color(color().as_int()); // reset color
        int x_min = point(0).x, x_max = point(0).x;
        int y_min = point(0).y, y_max = point(0).y;
    
        // establish bounding box
        for(int i=1; i<number_of_points(); i++){
            if(point(i).x < x_min) x_min = point(i).x;
            if(point(i).x > x_max) x_max = point(i).x;
    
            if(point(i).y < y_min) y_min = point(i).y;
            if(point(i).y > y_max) y_max = point(i).y;
        }

        x_min-=1; x_max+=1;

        Point intersect{0,0};
        vector<int> x_intersects;
    
        for(int i=y_min; i<y_max; i+=line_gap){
            x_intersects.clear();

            for(int j=0; j<number_of_points(); j++){
                if(j==number_of_points()-1){
                    if(line_intersect(point(j), point(0), Point{x_min, i}, Point{x_max, i}, intersect))
                    {
                        x_intersects.push_back(intersect.x);
                    }
                }else{
                    if(line_intersect(point(j), point(j+1), Point{x_min, i}, Point{x_max, i}, intersect))
                    {
                        x_intersects.push_back(intersect.x);
                    }
                }
            }
            sort(x_intersects);
    
            for(int j=0; j<x_intersects.size(); j+=2){
                fl_line(x_intersects[j], i, x_intersects[j+1], i);
            }
        }
    }
}