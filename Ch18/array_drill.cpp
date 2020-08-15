/*
    array_drill.cpp

    Revision History:
*/

#include "../std_lib_facilities.h"

/****************************************
*           CLASS DEFINITIONS
****************************************/

/****************************************
*           FUNCTION PROTOTYPES
****************************************/

void f(int array[], int size);
int fact(int n);

/****************************************
*           GLOBAL VARIABLES
****************************************/

// global array of 10 ints
constexpr int ga_size = 10;
int ga[ga_size] = {1, 2, 4, 8, 16,
			32, 64, 128, 256, 512};

/****************************************
*             MAIN FUNCTION
****************************************/

int main(){
    try{
    	f(ga, ga_size);

    	int aa[10];

    	for(int i=0; i<10; i++)
    		aa[i] = fact(i+1);

    	f(aa, 10);
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

void f(int array[], int size){
	int la[ga_size];

	for(int i=0; i<ga_size; i++){
		la[i] = ga[i];
	}

	for(int i=0; i<size; i++)
		cout << la[i] << ' ';

	cout << '\n';

	int* p = new int[size];

	for(int i=0; i<size; i++)
		*(p+i) = array[i];

	for(int i=0; i<size; i++)
		cout << *(p+i) << ' ';

	cout << '\n';

	delete[] p;
}

int fact(int n){
	if(n<0) error("Factorial of negative numbers is undefined");

	if(n<2) return 1;

	return n * fact(n-1);
}
