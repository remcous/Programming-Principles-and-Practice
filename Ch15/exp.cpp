/*
    graphingSimpleFunctions.cpp

    Revision History:
*/

#include "../std_lib_facilities.h"
#include "../Libraries/Simple_window.h"
#include "../Libraries/Graph.h"

/****************************************
*           CLASS DEFINITIONS
****************************************/

/****************************************
*           FUNCTION PROTOTYPES
****************************************/

double fac(int n);					// factorial(n): n!
double term(double x, int n){return pow(x,n)/fac(n);}	// nth term of series
double expe(double x, int n);	// sum of n terms for x

/****************************************
*           GLOBAL VARIABLES
****************************************/

constexpr int xmax = 800;                 // window size
constexpr int ymax = 600;

constexpr int x_orig = xmax/2;         // position of (0,0) is center of window
constexpr int y_orig = ymax/2;
const Point orig {x_orig,y_orig};

constexpr int r_min = -10;		// range [-10,11)
constexpr int r_max = 11;

constexpr int n_points = 400;	// number of points used in range

constexpr int x_scale = 30;		// scaling factors
constexpr int y_scale = 30;

/****************************************
*             MAIN FUNCTION
****************************************/

int main(){
    try{
        Simple_window win{Point{100,100}, xmax, ymax, "Real exp"};

         // Add x and y axis to plot
        constexpr int xlength = xmax - 40;  // make the axis a bit smaller than the window
        constexpr int ylength = ymax - 40;

        Axis x{Axis::x, Point{20,y_orig}, xlength, 
            xlength/x_scale, "one notch == 1"};
        Axis y{Axis::y, Point{x_orig,ylength+20}, 
            ylength, ylength/y_scale, "one notch == 1"};

        x.set_color(Color::red);
        y.set_color(Color::red);
        x.label.move(-160,0);
        x.notches.set_color(Color::dark_red);

        win.attach(x);
        win.attach(y);

        // "real" exp function

        Function real_exp{exp, r_min, r_max, orig, n_points/2, x_scale, y_scale};
        real_exp.set_color(Color::blue);

        win.attach(real_exp);
        win.wait_for_button();

        for(int n=0; n<50; n++){
            ostringstream ss;
            ss << "exp approximation; n==" << n;
            win.set_label(ss.str());

            // get next approximation
            Function e {[n](double x){return expe(x,n);},r_min,r_max,orig,200,x_scale,y_scale};
            win.attach(e);
            win.wait_for_button();
            win.detach(e);
        }
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

double fac(int n){
	double r = 1;
	while(n>1){
		r*=n;
		--n;
	}

	return r;
}

double expe(double x, int n){
	double sum = 0;
	for(int i=0; i<n; ++i) sum+=term(x,i);
	return sum;
}