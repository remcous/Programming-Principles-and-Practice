/*
    exercise6.cpp

	Analog clock

    Revision History:
*/

#include "../Libraries/std_lib_facilities.h"
#include "../Libraries/Simple_window.h"
#include "../Libraries/Graph.h"
#include "../Libraries/GUI.h"
#include <ctime>
#include <unistd.h>

/****************************************
*           CLASS DEFINITIONS
****************************************/

class Clock : Graph_lib::Window{
public:
	Clock(Point xy, int w, const string& title);

	static void cb_run_clock(void* p);
private:
	// DATA
	Vector_ref<Shape> face;
	time_t current_time;
	struct tm* time_data;
	int r_face, r_hour, r_minute, r_second;
	Point center;
	Line *hr;
	Line *min;
	Line *sec;
	Text label_am_pm;

	// Functions
	void draw_face();
	void update_time();
	void draw_time();

	// Widget
	Button quit_button;

	// Actions
	void quit();

	// Callbacks
	static void cb_quit(Address, Address pw);
};

/****************************************
*           FUNCTION PROTOTYPES
****************************************/

/****************************************
*           GLOBAL VARIABLES
****************************************/

#define WIDTH 600

/****************************************
*             MAIN FUNCTION
****************************************/

int main(){
    try{
        Clock win{Point{100,100}, WIDTH, "Clock"};
        Fl::add_timeout(1.0, Clock::cb_run_clock, &win);
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
*       FUNCTION DEFINITIONS - Clock
****************************************/

Clock::Clock(Point xy, int w, const string& title)
	:Window{xy, w, w+20, title},
	quit_button{Point{x_max()/2-35, 0}, 70,20, "Quit", cb_quit},
	r_face{(w-20)/2}, r_minute{(w-40)/2}, r_hour{w/4}, r_second{(w-40)/2},
	center{w/2, w/2+20},
	hr{NULL}, min{NULL}, sec{NULL},
	label_am_pm{Point{x_max()/2, (y_max()-20)/4+20}, "AM"}
{
	attach(quit_button);
	draw_face();
	label_am_pm.set_color(Color::black);
	attach(label_am_pm);
	update_time();
	draw_time();
}

void Clock::draw_face(){
	face.push_back(new Circle{center, r_face});
	face[0].set_fill_color(Color::white);

	face.push_back(new Circle{center, r_face/10});
	face[1].set_color(Color::black);
	face[1].set_fill_color(Color::black);

	for(double angle = 0; angle <= 2*M_PI; angle += (M_PI/6)){
		face.push_back(new Line{Point{center.x + r_face * cos(angle),
											center.y + r_face * sin(angle)},
										Point{center.x + 15.0/16* r_face * cos(angle),
											center.y + 15.0/16* r_face * sin(angle)}});
	}

	for(int i=0; i< face.size(); i++)
	{
		face[i].set_color(Color::black);
		attach(face[i]);
	}
}

void Clock::update_time(){
	time(&current_time);
	time_data = localtime(&current_time);
}

void Clock::draw_time(){
	// deallocate dynamically assigned Line objects
	if(hr){
		detach(*hr);
		delete hr;
	}
	if(min){
		detach(*min);
		delete min;
	}
	if(sec){
		detach(*sec);
		delete sec;
	}
	
	// Calculate the angle and create the new Line objects
	double a_hr, a_min, a_sec;

	if(time_data->tm_hour < 12){
		a_hr = M_PI/2 - (double)(time_data->tm_hour)/12*(2*M_PI);
		label_am_pm.set_label("AM");
	}else{
		a_hr = M_PI/2 - (double)(time_data->tm_hour-12)/12*(2*M_PI);
		label_am_pm.set_label("PM");
	}

	a_hr -= (double)(time_data->tm_min)/60 * (M_PI/6);

	a_min = M_PI/2 - (double)(time_data->tm_min)/60*(2*M_PI);
	a_sec = M_PI/2 - (double)(time_data->tm_sec)/60*(2*M_PI);

	hr = new Line{center, Point{center.x + r_hour*cos(a_hr),
		center.y - r_hour*sin(a_hr)}};
	min = new Line{center, Point{center.x + r_minute*cos(a_min),
		center.y - r_minute*sin(a_min)}};
	sec = new Line{center, Point{center.x + r_second*cos(a_sec),
		center.y - r_second*sin(a_sec)}};

	// Styling
	hr->set_color(Color::black);
	min->set_color(Color::black);
	sec->set_color(Color::red);

	hr->set_style(Line_style{Line_style::solid, 8});
	min->set_style(Line_style{Line_style::solid, 4});
	sec->set_style(Line_style{Line_style::solid, 1});

	// draw to window
	attach(*hr);
	attach(*min);
	attach(*sec);

	redraw();
}

void Clock::quit(){
	hide();
}

void Clock::cb_quit(Address, Address pw){
	reference_to<Clock>(pw).quit();
}

void Clock::cb_run_clock(void* p){
	Clock* c = (Clock*)p;
	c->update_time();
	c->draw_time();
	Fl::repeat_timeout(1.0, Clock::cb_run_clock, p);
}