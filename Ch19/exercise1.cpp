/*
    exercise1.cpp

    Revision History:
*/

#include "../Libraries/std_lib_facilities.h"

/****************************************
*           CLASS DEFINITIONS
****************************************/

/****************************************
*           FUNCTION PROTOTYPES
****************************************/

template<typename T> vector<T> f(const vector<T> &a, const vector<T> &b);

/****************************************
*           GLOBAL VARIABLES
****************************************/

/****************************************
*             MAIN FUNCTION
****************************************/

int main(){
    try{
        vector<int> v1 = {1, 2, 3, 4, 5};
        vector<int> v2 = {9, 8, 7, 6};
        
        v1 = f(v1, v2);
        
        for(int num : v1)
        	cout << num << ' ';
        cout << endl;

        v2 = f(v2, v1);

        for(int num : v2)
        	cout << num << ' ';
        cout << endl;
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

template<typename T> vector<T> f(const vector<T> &a, const vector<T> &b)
{
	vector<T> result(a.size());

	for(int i=0; i<a.size(); i++)
	{
		if(i >= b.size()) result[i] = a[i];
		else result[i] = a[i] + b[i];
	}

	return result;
}