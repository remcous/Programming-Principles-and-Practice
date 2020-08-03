/*
    exercise11.cpp

    Revision History:
    	ex 11 - implement a Binary_tree class that derives from Shape
    	ex 12 - create a Triangle_binary_tree class that derives from
    			Binary_tree but uses triangular nodes instead of circular
    	ex 13 - Modify Binary_tree to be able to set lines to have arrows 
    			pointing up or down as set by a parameter
*/

#include "../std_lib_facilities.h"
#include "Simple_window.h"
#include "Graph.h"

/****************************************
*           CLASS DEFINITIONS
****************************************/

class Binary_tree : public Shape{
public:
	enum class Line_type{
		solid, arrow_up, arrow_down
	};

	Binary_tree(Point root);
	Binary_tree(Point root, int level);
	Binary_tree(Point root, int level, Line_type lt);

	void draw_lines() const;
	virtual void draw_nodes() const;

	int get_radius() const{return r;}
	void set_radius(int rr){r = rr;}

	int get_dx() const{return dx;}
	void set_dx(int x){dx = x;}

	int get_dy() const{return dy;}
	void set_dy(int y){dy = y;}

	Line_type get_line_type() const{return line_type;}
	void set_line_type(Line_type lt){line_type = lt;}
protected:
	Line_type line_type;
	int l;
	int r{5};
	int dx{20};
	int dy{20};
};

class Triangle_binary_tree : public Binary_tree{
public:
	Triangle_binary_tree(Point root)
		:Binary_tree{root}{}
	Triangle_binary_tree(Point root, int level)
		:Binary_tree{root, level}{}
	Triangle_binary_tree(Point root, int level, 
		Binary_tree::Line_type lt)
			:Binary_tree{root, level, lt}{}

	void draw_nodes() const;
};

struct Arrow : public Shape{
    Arrow(Point a, Point b);

    void draw_lines() const;
};

/****************************************
*           FUNCTION PROTOTYPES
****************************************/

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

        Simple_window win{tl, WIDTH, HEIGHT, "Chapter 14 - Exercise 11"};

        Binary_tree bt{Point{WIDTH/2, 100},5, Binary_tree::Line_type::arrow_up};

        bt.set_color(Color::black);
        bt.set_fill_color(Color::red);

        win.attach(bt);
        
        Triangle_binary_tree tbt{Point{WIDTH/2, 400},6};

        tbt.set_color(Color::black);
        tbt.set_fill_color(Color::red);
        tbt.set_line_type(Binary_tree::Line_type::arrow_down);

        tbt.set_radius(10);

        win.attach(tbt);
		
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
    fl_color(color().as_int()); // reset color
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

Binary_tree::Binary_tree(Point root)
	:l{1}, line_type{Line_type::solid}
{
	add(root);
}

Binary_tree::Binary_tree(Point root, int levels)
	:l{levels}, line_type{Line_type::solid}
{
	if(l<0) error("Binary tree must have atleast 0 levels");
	if(l==0) return;
	add(root);	// levels = 1
	for(int i=2; i<=levels; i++){
		for(int j=0; j<pow(2,i-1); j++){
			static int x,y;
			x = root.x - ((pow(2,i-1)-1)/2.0-j)*pow(2,levels-i)*dx;
			y = root.y + (i-1)*dy;
			add(Point(x,y));
		}
	}
}

Binary_tree::Binary_tree(Point root, int level, Line_type lt)
	:Binary_tree{root, level}
{
	line_type = lt;
}

void Binary_tree::draw_lines() const{
	if(color().visibility()){
		fl_color(color().as_int());

		switch(line_type){
		case Line_type::solid:
			for(int i=0; i<number_of_points()/2; i++){
				fl_line(point(i).x, point(i).y, point(2*i+1).x, point(2*i+1).y);
				fl_line(point(i).x, point(i).y, point(2*i+2).x, point(2*i+2).y);
			}
			break;
		case Line_type::arrow_down:
			for(int i=0; i<number_of_points()/2; i++){
				static Point a, b;
				static double x, y;

				// LEFT NODE
				a = Point{point(i).x, point(i).y};
				b = Point{point(2*i+1).x, point(2*i+1).y};
				fl_line(a.x, a.y, b.x, b.y);

				// unit vectors in x and y
				x = (b.x - a.x)/sqrt(pow(b.x-a.x, 2) + pow(b.y-a.y, 2));
    			y = (b.y - a.y)/sqrt(pow(b.x-a.x, 2) + pow(b.y-a.y, 2));

    			fl_line(b.x, b.y, b.x-10*x+5*y, b.y-10*y-5*x);
    			fl_line(b.x-10*x+5*y, b.y-10*y-5*x, b.x-10*x-5*y, b.y-10*y+5*x);
    			fl_line(b.x-10*x-5*y, b.y-10*y+5*x, b.x, b.y);

    			// Fill arrowhead
    			fl_begin_complex_polygon();
		        fl_vertex(b.x, b.y);
		        fl_vertex(b.x-10*x+5*y, b.y-10*y-5*x);
		        fl_vertex(b.x-10*x-5*y, b.y-10*y+5*x);
		        fl_end_complex_polygon();

    			// RIGHT NODE
    			b = Point{point(2*i+2).x, point(2*i+2).y};
				fl_line(a.x, a.y, b.x, b.y);

				// unit vectors in x and y
				x = (b.x - a.x)/sqrt(pow(b.x-a.x, 2) + pow(b.y-a.y, 2));
    			y = (b.y - a.y)/sqrt(pow(b.x-a.x, 2) + pow(b.y-a.y, 2));

    			fl_line(b.x, b.y, b.x-10*x+5*y, b.y-10*y-5*x);
    			fl_line(b.x-10*x+5*y, b.y-10*y-5*x, b.x-10*x-5*y, b.y-10*y+5*x);
    			fl_line(b.x-10*x-5*y, b.y-10*y+5*x, b.x, b.y);

    			// Fill arrowhead
    			fl_begin_complex_polygon();
		        fl_vertex(b.x, b.y);
		        fl_vertex(b.x-10*x+5*y, b.y-10*y-5*x);
		        fl_vertex(b.x-10*x-5*y, b.y-10*y+5*x);
		        fl_end_complex_polygon();
			}
			break;
		case Line_type::arrow_up:
			for(int i=0; i<number_of_points()/2; i++){
				static Point a, b;
				static double x, y;

				// LEFT NODE
				b = Point{point(i).x, point(i).y};
				a = Point{point(2*i+1).x, point(2*i+1).y};
				fl_line(a.x, a.y, b.x, b.y);

				// unit vectors in x and y
				x = (b.x - a.x)/sqrt(pow(b.x-a.x, 2) + pow(b.y-a.y, 2));
    			y = (b.y - a.y)/sqrt(pow(b.x-a.x, 2) + pow(b.y-a.y, 2));

    			fl_line(b.x, b.y, b.x-10*x+5*y, b.y-10*y-5*x);
    			fl_line(b.x-10*x+5*y, b.y-10*y-5*x, b.x-10*x-5*y, b.y-10*y+5*x);
    			fl_line(b.x-10*x-5*y, b.y-10*y+5*x, b.x, b.y);

    			// Fill arrowhead
    			fl_begin_complex_polygon();
		        fl_vertex(b.x, b.y);
		        fl_vertex(b.x-10*x+5*y, b.y-10*y-5*x);
		        fl_vertex(b.x-10*x-5*y, b.y-10*y+5*x);
		        fl_end_complex_polygon();

    			// RIGHT NODE
    			a = Point{point(2*i+2).x, point(2*i+2).y};
				fl_line(a.x, a.y, b.x, b.y);

				// unit vectors in x and y
				x = (b.x - a.x)/sqrt(pow(b.x-a.x, 2) + pow(b.y-a.y, 2));
    			y = (b.y - a.y)/sqrt(pow(b.x-a.x, 2) + pow(b.y-a.y, 2));

    			fl_line(b.x, b.y, b.x-10*x+5*y, b.y-10*y-5*x);
    			fl_line(b.x-10*x+5*y, b.y-10*y-5*x, b.x-10*x-5*y, b.y-10*y+5*x);
    			fl_line(b.x-10*x-5*y, b.y-10*y+5*x, b.x, b.y);

    			// Fill arrowhead
    			fl_begin_complex_polygon();
		        fl_vertex(b.x, b.y);
		        fl_vertex(b.x-10*x+5*y, b.y-10*y-5*x);
		        fl_vertex(b.x-10*x-5*y, b.y-10*y+5*x);
		        fl_end_complex_polygon();
			}
			break;
		default:
			error("Binary tree: Unknown line type");
		}
	}

	draw_nodes();
}

void Binary_tree::draw_nodes() const{
	fl_color(color().as_int());

	for(int i=0; i<number_of_points(); i++){
		fl_arc(point(i).x-r, point(i).y-r, r+r, r+r, 0, 360);
	}

	if(fill_color().visibility()){
        fl_color(fill_color().as_int());
		for(int i=0; i<number_of_points(); i++){
			fl_pie(point(i).x-r, point(i).y-r, r+r, r+r, 0, 360);
		}
		fl_color(color().as_int());
	}
}
/*
void Triangle_binary_tree::draw_lines() const{
	if(color().visibility()){
    	fl_color(color().as_int());

		for(int i=0; i<number_of_points(); i++){
			fl_line(point(i).x, point(i).y-r, point(i).x+sqrt(3)/2*r, point(i).y+r/2);
			fl_line(point(i).x+sqrt(3)/2*r, point(i).y+r/2, point(i).x-sqrt(3)/2*r, point(i).y+r/2);
			fl_line(point(i).x-sqrt(3)/2*r, point(i).y+r/2,point(i).x, point(i).y-r);
		}

		for(int i=0; i<number_of_points()/2; i++){
			fl_line(point(i).x, point(i).y, point(2*i+1).x, point(2*i+1).y);
			fl_line(point(i).x, point(i).y, point(2*i+2).x, point(2*i+2).y);
		}
	}

	if(fill_color().visibility()){
        fl_color(fill_color().as_int());
        for(int i=0; i<number_of_points(); i++){
    		fl_begin_complex_polygon();
            fl_vertex(point(i).x, point(i).y-r);
            fl_vertex(point(i).x+sqrt(3)/2*r, point(i).y+r/2);
            fl_vertex(point(i).x-sqrt(3)/2*r, point(i).y+r/2);
            fl_end_complex_polygon();
        }
		fl_color(color().as_int());
	}
}*/

void Triangle_binary_tree::draw_nodes() const{
	if(color().visibility()){
    	fl_color(color().as_int());

		for(int i=0; i<number_of_points(); i++){
			fl_line(point(i).x, point(i).y-r, point(i).x+sqrt(3)/2*r, point(i).y+r/2);
			fl_line(point(i).x+sqrt(3)/2*r, point(i).y+r/2, point(i).x-sqrt(3)/2*r, point(i).y+r/2);
			fl_line(point(i).x-sqrt(3)/2*r, point(i).y+r/2,point(i).x, point(i).y-r);
		}
	}

	if(fill_color().visibility()){
        fl_color(fill_color().as_int());
        for(int i=0; i<number_of_points(); i++){
    		fl_begin_complex_polygon();
            fl_vertex(point(i).x, point(i).y-r);
            fl_vertex(point(i).x+sqrt(3)/2*r, point(i).y+r/2);
            fl_vertex(point(i).x-sqrt(3)/2*r, point(i).y+r/2);
            fl_end_complex_polygon();
        }
		fl_color(color().as_int());
	}
}