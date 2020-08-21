/*
    template_drill.cpp

    Revision History:
*/

#include "../std_lib_facilities.h"

/****************************************
*           CLASS DEFINITIONS
****************************************/

template<typename T> struct S{
public:
	S(T t):val{t}{}

	T& operator=(const T& t);

	T& get();
	const T& get() const;
	void set(T t);
private:
	T val;
};

/****************************************
*           FUNCTION PROTOTYPES
****************************************/

template<typename T> void read_val(T& v);
template<typename T> istream& operator>>(istream& is, vector<T>& v);
template<typename T> ostream& operator<<(ostream& os, vector<T>& v);

/****************************************
*           GLOBAL VARIABLES
****************************************/

/****************************************
*             MAIN FUNCTION
****************************************/

int main(){
    try{
        S<int> sint{5};
        S<char> schar{'r'};
        S<double> sdouble{3.14};
        S<string> sstring{"Hello"};
        S<vector<int>> svector{{1,2,3}};

        cout << sint.get() << schar.get() << sdouble.get()
        	<< sstring.get() << svector.get()[1];

        S<int> sint2 = 7;

        cout << "\n\n" << sint2.get() << endl;

        cout << "Enter a value into S<int>: ";
        read_val(sint.get());
        cout << "S<int> is holding " << sint.get() << '\n';

        cout << "Enter a value into S<char>: ";
        read_val(schar.get());
        cout << "S<char> is holding " << schar.get() << '\n';

        cout << "Enter a value into S<double>: ";
        read_val(sdouble.get());
        cout << "S<double> is holding " << sdouble.get() << '\n';

        cout << "Enter a value into S<string>: ";
        read_val(sstring.get());
        cout << "S<string> is holding " << sstring.get() << '\n';

        cout << "Enter a value into S<vector<int>>: ";
        read_val(svector.get());
        cout << "S<vector<int>> is holding " << svector.get() << '\n';
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

template<typename T> T& S<T>::get(){
	return val;
}

template<typename T> const T& S<T>::get() const{
	return val;
}

template<typename T> void S<T>::set(T t){
	val = t;
}

template<typename T> T& S<T>::operator=(const T& t){
	if(this == &t) return *this;

	val = t;
	return val;
}

template<typename T> void read_val(T& v){
	cin >> v;

	// clear the buffer
	cin.clear();
	fflush(stdin);
}

template<typename T> istream& operator>>(istream& is, vector<T>& v){
	char ch;
	T temp;
	
	is.get(ch);
	if(ch != '{') error("Input error: vector<T> input must begin with {");

	while(is >> temp)
	{
		v.push_back(temp);
		is.get(ch);
		if(ch == '}') break;
		if(ch != ',') error("Input error: vector<T> input separated by \', \'");
	}

	return is;
}

template<typename T> ostream& operator<<(ostream& os, vector<T>& v){
	os << '{';

	for(int i=0; i<v.size(); i++){
		os << v[i];
		if(i == v.size()-1) os << '}';
		else os << ", ";
	}

	os << '}';

	return os;
}
