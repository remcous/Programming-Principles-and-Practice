/*
    exercise12.cpp

    draw a superellipse using N points

    abs(x/a)^m + abs(y/b)^n = 1 
    for m,n>0

    Revision History:
*/

#include "../std_lib_facilities.h"
#include "Simple_window.h"
#include "Graph.h"
#include <cmath>

/****************************************
*           FUNCTION PROTOTYPES
****************************************/

int sgn(double num);

/****************************************
*           GLOBAL VARIABLES
****************************************/

#define WIDTH 800
#define HEIGHT 800
#define CENTER_X WIDTH/2
#define CENTER_Y HEIGHT/2

/****************************************
*             MAIN FUNCTION
****************************************/

int main(){
    try{
        int a,b,N;
        double m,n;

        cout << "Governing equation:\n\n";
        cout << "\t|x|^m   |y|^n\n"
             << "\t|-|   + |-|   = 1\n"
             << "\t|a|     |b|\n\n";
        cout << "for m,n>0\nUsing N points for approximation\n\n";

        cout << "N = ";
        cin >> N;
        if(N<1) error("N > 0 required for approximation");

        cout << "a = ";
        cin >> a;

        cout << "m = ";
        cin >> m;
        if(m<=0) error("m > 0 required");
        
        cout << "b = ";
        cin >> b;
        
        cout << "n = ";
        cin >> n;
        if(n<=0) error("n > 0 required");
        
        int scale;

        {
            int scale_x = CENTER_X / a;
            int scale_y = CENTER_Y / b;
            if(scale_x > scale_y) scale = scale_y;
            else scale = scale_x;
        }

        vector<Point> points;
        constexpr double pi = 3.14159;

        double x,y;

        for(double t=0; t<=2*pi; t += ((2*pi)/N)){
            x = scale * pow(abs(cos(t)), 2/m) * a * sgn(cos(t)) + CENTER_X;
            y = scale * pow(abs(sin(t)), 2/n) * b * sgn(sin(t)) + CENTER_Y;

            /*cout << fixed << setprecision(4) << t << '\t' 
                << setprecision(0) << x << ' ' << y << endl;
            */
            points.push_back(Point{x,y});
        }

        Point tl{100,100};
        Simple_window win{tl, WIDTH, HEIGHT, "Exercise 12"};

        Closed_polyline superellipse;

        for(Point point : points){
            superellipse.add(point);
        }

        superellipse.set_color(Color::black);
        superellipse.set_fill_color(Color::red);

        Axis xa{Axis::x, Point{0,CENTER_Y}, WIDTH, WIDTH/scale, ""}; // make an axis
        Axis ya{Axis::y, Point{CENTER_X,HEIGHT}, HEIGHT, HEIGHT/scale, ""};

        xa.set_color(Color::black);
        ya.set_color(Color::black);

        win.attach(superellipse);
        win.attach(xa);
        win.attach(ya);

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
*       FUNCTION DEFINITIONS - GLOBAL
****************************************/

int sgn(double num){
    if(num>0) return 1;
    else if(num<0) return -1;
    return 0;
}