/*
    exercise4.cpp

    Revision History:
*/

#include "../Libraries/std_lib_facilities.h"
#include "../Libraries/Simple_window.h"
#include "../Libraries/Graph.h"
#include "../Libraries/GUI.h"

/****************************************
*           CLASS DEFINITIONS
****************************************/

class Draw_window : Graph_lib::Window{
public:
	Draw_window(Point xy, int w, int h, const string& title);
private:
	// DATA
	Vector_ref<Shape> shape_list;

	// WIDGETS
	In_box next_x;
	In_box next_y;
	In_box next_rad;
	Menu shape_menu;
	Button quit_button;
	Button undo_button;

	// ACTIONS
	void draw_circle();
	void draw_square();
	void draw_triangle();
	void draw_hexagon();
	void quit();
	void undo();

	// CALLBACKS
	static void cb_circle(Address, Address pw);
	static void cb_square(Address, Address pw);
	static void cb_triangle(Address, Address pw);
	static void cb_hexagon(Address, Address pw);
	static void cb_quit(Address, Address pw);
	static void cb_undo(Address, Address pw);
};

/****************************************
*           FUNCTION PROTOTYPES
****************************************/

/****************************************
*           GLOBAL VARIABLES
****************************************/

#define WIDTH 800
#define HEIGHT 600

/****************************************
*             MAIN FUNCTION
****************************************/

int main(){
    try{
        Draw_window win{Point{100,100}, WIDTH, HEIGHT, 
        	"Chapter 16 - Exercise 4"};
        return gui_main();
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
*	FUNCTION DEFINITIONS - Draw_window
****************************************/

Draw_window::Draw_window(Point xy, int w, int h, const string& title)
	:Window{xy, w, h, title},
	next_x{Point{20,0}, 70, 20, "x:"},
	next_y{Point{120,0}, 70, 20, "y:"},
	next_rad{Point{250,0}, 70, 20, "radius:"},
	shape_menu{Point{x_max()-460, 0}, 70,20, Menu::horizontal, ""},
	quit_button{Point{x_max()-70, 0}, 70, 20, "Quit", cb_quit}
{
	attach(next_x);
	attach(next_y);
	attach(next_rad);
	shape_menu.attach(new Button{Point{0,0}, 0,0, "Circle", cb_circle});
	shape_menu.attach(new Button{Point{0,0}, 0,0, "Square", cb_square});
	shape_menu.attach(new Button{Point{0,0}, 0,0, "Triangle", cb_triangle});
	shape_menu.attach(new Button{Point{0,0}, 0,0, "Hexagon", cb_hexagon});
	attach(shape_menu);
	attach(quit_button);
}

void Draw_window::draw_circle(){
	// get position and size data from In_box Widgets
	int x = next_x.get_int();
	int y = next_y.get_int();
	int r = next_rad.get_int();

	shape_list.push_back(new Circle{Point{x,y}, r});
	attach(shape_list[shape_list.size()-1]);

	redraw();
}

void Draw_window::draw_square(){
	// get position and size data from In_box Widgets
	int x = next_x.get_int();
	int y = next_y.get_int();
	int r = next_rad.get_int() / sqrt(2);

	shape_list.push_back(new Rectangle{Point{x-r, y-r}, r+r, r+r});
	attach(shape_list[shape_list.size()-1]);

	redraw();
}

void Draw_window::draw_triangle(){
	// get position and size data from In_box Widgets
	int x = next_x.get_int();
	int y = next_y.get_int();
	int r = next_rad.get_int();

	Closed_polyline* cpl = new Closed_polyline{};

	constexpr int sides = 3;

	double initial_angle = -M_PI/2;
	double increment = 2 * M_PI / sides;

	for(double angle = initial_angle; angle<=(2*M_PI + initial_angle);
		angle += increment)
	{
		cpl->add(Point{x+cos(angle)*r, y+sin(angle)*r});
	}

	shape_list.push_back(cpl);
	attach(shape_list[shape_list.size()-1]);

	redraw();
}

void Draw_window::draw_hexagon(){
	// get position and size data from In_box Widgets
	int x = next_x.get_int();
	int y = next_y.get_int();
	int r = next_rad.get_int();

	Closed_polyline* cpl = new Closed_polyline{};

	constexpr int sides = 6;

	double initial_angle = 0;
	double increment = 2 * M_PI / sides;

	for(double angle = initial_angle; angle<=(2*M_PI + initial_angle);
		angle += increment)
	{
		cpl->add(Point{x+cos(angle)*r, y+sin(angle)*r});
	}

	shape_list.push_back(cpl);
	attach(shape_list[shape_list.size()-1]);

	redraw();
}

void Draw_window::quit(){
	hide();	// FLTK quit function to delete window
}

void Draw_window::undo(){	// remove the last shape added
	// No Vector_ref method to remove an element from list

}

/****************************************
*			CALLBACK FUNCTIONS
****************************************/

void Draw_window::cb_circle(Address, Address pw){
	reference_to<Draw_window>(pw).draw_circle();
}

void Draw_window::cb_square(Address, Address pw){
	reference_to<Draw_window>(pw).draw_square();
}

void Draw_window::cb_triangle(Address, Address pw){
	reference_to<Draw_window>(pw).draw_triangle();
}

void Draw_window::cb_hexagon(Address, Address pw){
	reference_to<Draw_window>(pw).draw_hexagon();
}

void Draw_window::cb_quit(Address, Address pw){
	reference_to<Draw_window>(pw).quit();
}

void Draw_window::cb_undo(Address, Address pw){
	reference_to<Draw_window>(pw).undo();
}
