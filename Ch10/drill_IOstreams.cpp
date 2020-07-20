#include "../std_lib_facilities.h"

/**********************************
*		 	 CONSTANTS
**********************************/

#define FILE "mydata.txt"
#define NUM_VALUES 7

/**********************************
*		  CLASS DEFINITION
**********************************/

class Point{
public:
	Point(double xx, double yy)
		:x{xx}, y{yy}
		{}
	Point():x{0},y{0}{}
	double get_x() const{return x;}
	double get_y() const{return y;}
	void set_coords(double xx, double yy);
private:
	double x, y;
};

/**********************************
*		  FUNCTION PROTOTYPE
**********************************/

istream& operator>>(istream& is, Point& p);
ostream& operator<<(ostream& os, const Point& p);
bool operator==(const Point& a, const Point& b);

/**********************************
*		  	MAIN PROGRAM
**********************************/

int main(){
	vector<Point> original_points, processed_points;

	cout << "Please enter " << NUM_VALUES 
		<< " pairs of coordinates:\n";

	for(int i=0; i<NUM_VALUES; i++){
		static Point p;
		cin >> p;
		original_points.push_back(p);
	}

	// FILE OUTPUT OF POINT VECTOR
	try{
		ofstream ofs{FILE};
		if(!ofs) error("Can't open output file ", FILE);
		for(Point p : original_points){
			ofs << p;
		}


	}catch(exception& e){
		cerr << e.what() << '\n';
	}
	
	// FILE INPUT OF POINT VECTOR
	try{
		ifstream ifs{FILE};
		if(!ifs) error("Can't open input file ", FILE);
		Point p;
		while(ifs >> p){
			processed_points.push_back(p);
		}	
	}catch(exception& e){
		cerr << e.what() << '\n';
	}
	
	cout << "Original\tProcessed\n";
	for(int i=0; i<original_points.size(); i++){
		cout << original_points[i] << "\t\t" 
			<< processed_points[i] << '\n';
	}

	if(original_points.size() != processed_points.size()){
		cerr << "Oops: Something went wrong";
	}
	else{
		bool matching = true;
		for(int i=0; i< original_points.size(); i++){
			if(!(matching = original_points[i] == processed_points[i]))
				break;
		}

		matching ? cout << "The vectors match!\n" : cerr << "Oops: something went wrong";
	}
	
	return 0;
}

/**********************************
*		  FUNCTION DEFINITIONS
**********************************/

istream& operator>>(istream& is, Point& p){
	double xx, yy;
	while(true){
		if(is >> xx) break;
		if(is.eof()) return is;
		if(is.fail()){
			is.clear();
			for(char ch; is>>ch;){
				if(isdigit(ch) || ch=='-' || ch=='.'){
					is.unget();
					break;
				}
			}
		}else error("unrecoverable input error");
	}
	while(true){
		if(is >> yy) break;
		if(is.eof()) return is;
		if(is.fail()){
			is.clear();
			for(char ch; is>>ch;){
				if(isdigit(ch) || ch=='-' || ch=='.'){
					is.unget();
					break;
				}
			}
		}else error("unrecoverable input error");
	}
	p.set_coords(xx,yy);
	return is;
}

ostream& operator<<(ostream& os, const Point& p){
	double x = p.get_x();
	double y = p.get_y();
	os << '(' << x << ',' << y << ')';
	return os;
}

void Point::set_coords(double xx, double yy){
	x=xx;
	y=yy;
}

bool operator==(const Point& a, const Point& b){
	if(a.get_x() == b.get_x() && a.get_y() == b.get_y())
		return true;
	return false;
}