/*
    exercise3.cpp

    Revision History:
*/

#include "../Libraries/std_lib_facilities.h"

/****************************************
*           CLASS DEFINITIONS
****************************************/

template<typename A, typename B>
class Pair{
public:
	Pair(){}
	Pair(A v1, B v2): a{v1}, b{v2}{}

	const A& get_a() const{return a;}
	const B& get_b() const{return b;}
	void set_a(const A& val){a = val;}
	void set_b(const B& val){b = val;}
private:
	A a;
	B b;
};

/****************************************
*           FUNCTION PROTOTYPES
****************************************/

template<typename A, typename B>
ostream& operator<<(ostream& os, Pair<A,B>& p);

template<typename A, typename B>
istream& operator>>(istream& is, Pair<A,B>& p);

/****************************************
*           GLOBAL VARIABLES
****************************************/

/****************************************
*             MAIN FUNCTION
****************************************/

int main(){
    try{
    	vector<Pair<string, double>> symbol_table;
        symbol_table.push_back({"pi", 3.14159});
        symbol_table.push_back({"e", 2.71828});
        symbol_table.push_back({"NA", 6.022e23});
        symbol_table.push_back({"qe", 1.6022e-19});

        {
        	cout << "Enter a constant <string, double> space separated: ";
        	Pair<string, double> temp{};
        	cin >> temp;
        	symbol_table.push_back(temp);
        }

        for(Pair<string, double> symbol : symbol_table)
	    	cout << symbol << endl;
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

template<typename A, typename B>
ostream& operator<<(ostream& os, Pair<A,B>& p)
{
	os << p.get_a() << ' ' << p.get_b();
	return os;
}

template<typename A, typename B>
istream& operator>>(istream& is, Pair<A,B>& p)
{
	A temp_a;
	B temp_b;
	is >> temp_a >> temp_b;
	p.set_a(temp_a);
	p.set_b(temp_b);
}
