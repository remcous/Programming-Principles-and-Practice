/*
    Sierpinski.cpp

	Using recursion and graphics library to generate a 
	Sierpinski Triangle

    Revision History:
*/

#include "../std_lib_facilities.h"
#include "Simple_window.h"
#include "Graph.h"

/****************************************
*           CLASS DEFINITIONS
****************************************/

class Triangle : public Shape{
public:
	Triangle(Point bottom_left, int length)
		:l{length}
		{
			add(bottom_left);
		}

	void draw_lines() const;
private:
	int l;

	static constexpr double cos_60 = cos(M_PI/3);
	static constexpr double sin_60 = sin(M_PI/3);
};

/****************************************
*           FUNCTION PROTOTYPES
****************************************/

void Sierpinski(Point bl, int len);

/****************************************
*           GLOBAL VARIABLES
****************************************/

#define MIN_LEN 6
#define WIDTH 920
#define HEIGHT 800

Vector_ref<Triangle> t_list;

/****************************************
*             MAIN FUNCTION
****************************************/

int main(){
    try{
        Point tl{0,0};

        Simple_window win{tl, WIDTH, HEIGHT, "Sierpinki's Triangle"};

       	Sierpinski(Point{10,HEIGHT-10}, 900);

       	for(int i=0; i<t_list.size(); i++){
       		t_list[i].set_color(Color::black);
       		win.attach(t_list[i]);
       	}
		
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

void Triangle::draw_lines() const{
	if(color().visibility()){
		fl_color(color().as_int()); // reset color

		fl_line(point(0).x, point(0).y, point(0).x+l*cos_60, point(0).y-l*sin_60);
		fl_line(point(0).x+l*cos_60, point(0).y-l*sin_60, point(0).x+l, point(0).y);
		fl_line(point(0).x+l, point(0).y, point(0).x, point(0).y);
	}

	if (fill_color().visibility()) {
        fl_color(fill_color().as_int());
        fl_begin_complex_polygon();
        fl_vertex(point(0).x, point(0).y);
		fl_vertex(point(0).x+l*cos_60, point(0).y-l*sin_60);
		fl_vertex(point(0).x+l, point(0).y);
        fl_end_complex_polygon();
        fl_color(color().as_int()); // reset color
    }
}

void Sierpinski(Point bl, int len){
	if(len <= MIN_LEN)	// DEFAULT exit condition for recursion
		return;

	t_list.push_back(new Triangle{bl, len/2});
	Sierpinski(bl, len/2);

	t_list.push_back(new Triangle{Point{bl.x+cos(M_PI/3)*len/2+0.5, 
		bl.y-sin(M_PI/3)*len/2+0.5}, len/2});
	Sierpinski(Point{bl.x+cos(M_PI/3)*len/2+0.5, 
		bl.y-sin(M_PI/3)*len/2+0.5}, len/2);

	t_list.push_back(new Triangle{Point{bl.x+len/2, bl.y}, len/2});
	Sierpinski(Point{bl.x+len/2, bl.y}, len/2);
}
