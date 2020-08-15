/*
    vector_drill.cpp

    Revision History:
*/

#include "../std_lib_facilities.h"

/****************************************
*           CLASS DEFINITIONS
****************************************/

/****************************************
*           FUNCTION PROTOTYPES
****************************************/

void f(vector<int> vect);
int fact(int n);

/****************************************
*           GLOBAL VARIABLES
****************************************/

vector<int> gv = {
	1, 2, 4, 8, 16,
	32, 64, 128, 256, 512
};

/****************************************
*             MAIN FUNCTION
****************************************/

int main(){
    try{
        f(gv);

        vector<int> vv;

        for(int i=0; i<10; i++)
        	vv.push_back(fact(i+1));

        f(vv);
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

void f(vector<int> vect){
	vector<int> lv(gv.size());

	for(int i=0; i<lv.size(); i++)
		lv[i] = gv[i];

	for(int elem : lv)
		cout << elem << ' ';

	cout << endl;

	vector<int> lv2 = vect;

	for(int elem : lv2)
		cout << elem << ' ';

	cout << endl;
}

int fact(int n){
	if(n<0) error("Factorial of negative numbers is undefined");

	if(n<2) return 1;

	return n * fact(n-1);
}
