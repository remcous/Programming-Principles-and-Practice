/*
    vector.cpp

    Revision History:
*/

#include <iostream>

using namespace std;

/****************************************
*           CLASS DEFINITIONS
****************************************/

class vector{
	int sz;							// the size
	double* elem;					// pointer to the first element 
									// (of type double)
public:
	vector(int s)					// constructor
		:sz(s),						// initialize sz
		elem{new double[s]}			// initialize elem
		{
			for(int i=0; i<s; ++i) elem[i] = 0;	// initialize elements
		}
	~vector() 						// destructor
		{delete[] elem;}			// free memory

	int size() const{ return sz; }	// the current size
	double get(int n) const{return elem[n];}	// access: read
	void set(int n, double v){elem[n]=v;}		// access: write
};

/****************************************
*           FUNCTION PROTOTYPES
****************************************/

/****************************************
*           GLOBAL VARIABLES
****************************************/

/****************************************
*             MAIN FUNCTION
****************************************/

int main(){
    vector v{10};

    cout << v.size() << endl;

    return 0;
}

/****************************************
*       FUNCTION DEFINITIONS - vector
****************************************/