/*
    graphingDrill.cpp

    Revision History:
*/

#include "../Libraries/std_lib_facilities.h"
#include "../Libraries/Simple_window.h"
#include "../Libraries/Graph.h"

/****************************************
*           CLASS DEFINITIONS
****************************************/

struct Person{
public:
	Person():fn{""},ln{""},a{0}{}
	Person(string first_name, string last_name, int age);

	string first_name() const{return fn;}
	string last_name() const{return ln;}
	int age() const{return a;}
private:
	string fn, ln;
	int a;

	static constexpr int age_min = 0;
	static constexpr int age_max = 150;
	string invalid_char = ";:\"\'[]()*&^%$#@!,.<>/?{}\\|_=+~`";
};

/****************************************
*           FUNCTION PROTOTYPES
****************************************/

double one(double){return 1;}
double slope(double x){return x/2;}
double square(double x){return x*x;}
double sloping_cos(double x){return cos(x) + slope(x);}

istream& operator>>(istream& is, Person& p);
ostream& operator<<(ostream& os, const Person& p);

/****************************************
*           GLOBAL VARIABLES
****************************************/

constexpr int xmax = 600;		// window size
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
        /****************************
        *	CLASS DEFINITION DRILL	*
        ****************************/

        vector<Person> people;

        cout << "How many people would you like to add to the list: ";
        int num_people;
        cin >> num_people;

        if(num_people < 0) error("Cannot enter a negative number of people");
        else if(num_people == 0){}
        else if(num_people == 1) cout << "Enter the data for a person format: Auston Matthews 22\n";
        else cout << "Enter data for " << num_people << " people, format: Auston Matthews 22\n";

        for(int i=0; i < num_people; i++)
        {
        	Person temp;
        	cin >> temp;
        	people.push_back(temp);
        }

        cout << endl;

        for(Person temp : people){
        	cout << temp << '\n';
        }

        /****************************
        *		GRAPHING DRILL		*
        ****************************/

    	// SETUP WINDOW AND AXES
        Graph_lib::Window win{Point{100,100}, xmax, ymax, "Function Graphs"};

        Axis x{Axis::x, Point{100,y_orig}, 400, 20, "1 == 20 pixels"};
        Axis y{Axis::y, Point{x_orig,ymax-100}, 400, 20, "1 == 20 pixels"};

        x.set_color(Color::red);
        x.label.move(-130,-20);
        y.set_color(Color::red);

        win.attach(x);
        win.attach(y);

        // GRAPH FUNCTIONS
        Function s1{one, r_min, r_max, orig, n_points, 20, 20};

        Function s2{slope, r_min, r_max, orig, n_points, 20, 20};
        Text ts2{Point{s2.point(0).x - 20, s2.point(0).y + 20}, "x/2"};

        Function s3{square, r_min, r_max, orig, n_points, 20, 20};

        Function s4{cos, r_min, r_max, orig, n_points, 20, 20};
        s4.set_color(Color::blue);

        Function s5{sloping_cos, r_min, r_max, orig, n_points, 20, 20};

        // WINDOW ATTACHES
        win.attach(s1);
        win.attach(s2);
        win.attach(ts2);
        win.attach(s3);
        win.attach(s4);
        win.attach(s5);

        // KEEP OUTPUT ON SCREEN
        gui_main();
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

istream& operator>>(istream& is, Person& p){
	int a;
	string fn, ln;

	is >> fn >> ln >> a;

	p = Person{fn, ln, a};

	return is;
}

ostream& operator<<(ostream& os, const Person& p){
	os << p.first_name() << ' ' << p.last_name() << " " << p.age();

	return os;
}

Person::Person(string first_name, string last_name, int age)
	:fn{first_name}, ln{last_name}, a{age}
{
	if(age < age_min || age >= age_max)
		error("Person: Age out of bounds", age);

	for(char ch1 : fn){
		for(char ch2 : invalid_char){
			if(ch1 == ch2) error("Person: Invalid character in name: ", string{ch1});
		}
	}

	for(char ch1 : ln){
		for(char ch2 : invalid_char){
			if(ch1 == ch2) error("Person: Invalid character in name: ", string{ch1});
		}
	}
}