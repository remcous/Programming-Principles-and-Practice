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

// Prints 10 integers from an array 
// given a pointer to first element
void print_array10(ostream& os, int* a);
void print_array(ostream& os, int* a, int n);
void print_vector(ostream&os, vector<int> v);

/****************************************
*           GLOBAL VARIABLES
****************************************/

/****************************************
*             MAIN FUNCTION
****************************************/

int main(){
    try{
    	// Part 1-3
    	cout << "10 uninitialized ints:\n";
        int* array = new int[10];

        for(int i=0; i<10; i++) cout << *(array + i) << ' ';

        delete[] array;

    	// Part 4-6
    	cout << "\n\n10 initialized ints using print_array10():\n";
    	int array_size = 10;

    	array = new int[array_size];
    	for(int i=0; i<array_size; i++) *(array+i) = 100 + i;

    	print_array10(cout, array);

    	delete[] array;

    	cout << "\n\n11 initialized ints using print_array10():\n";
    	array_size = 11;

    	array = new int[array_size];
    	for(int i=0; i<array_size; i++) *(array+i) = 100 + i;

    	print_array10(cout, array);

    	delete[] array;

    	// Part 8-9
    	cout << "\n\n20 initialized ints using print_array():\n";
    	array_size = 20;

    	array = new int[array_size];
    	for(int i=0; i<array_size; i++) *(array+i) = 100 + i;

    	print_array(cout, array, array_size);

    	delete[] array;

    	// repeat of parts 5,6, and 8 using vector and print_vector()
    	cout << "\n\nVector w/ 10 elements using print_vector():\n";
    	vector<int> vect;
    	array_size = 10;

    	for(int i=0; i<array_size; i++)
    		vect.push_back(100+i);

    	print_vector(cout, vect);
    	vect.clear();

    	cout << "\n\nVector w/ 11 elements using print_vector():\n";
    	array_size = 11;

    	for(int i=0; i<array_size; i++)
    		vect.push_back(100+i);

    	print_vector(cout, vect);
    	vect.clear();

    	cout << "\n\nVector w/ 20 elements using print_vector():\n";
    	array_size = 20;

    	for(int i=0; i<array_size; i++)
    		vect.push_back(100+i);

    	print_vector(cout, vect);
    	vect.clear();

    	cout << "\n\nPART TWO:\n\n";

    	// Second part of drill

    	int num  = 7;
    	int* p1 = &num;

    	cout << p1 << " : " << *p1 << endl;

    	array_size = 7;

    	int* p2 = new int[array_size];

    	for(int i=0; i<array_size; i++)
    		*(p2+i) = pow(2,i);

    	cout << "\n" << p2 << ":\n";

    	for(int i=0; i<array_size; i++)
    		cout << *(p2+i) << ' ';

    	int* p3 = p2;

    	p2 = p1;
    	p2 = p3;

    	cout << "\n\np1 " << p1 << " : " << *p1;
    	cout << "\n\np2 " << p2 << " : " << *p2;

    	delete[] p2;

    	// Part 10-12 : create two arrays, 
    	// assign values to one and copy using pointers
    	cout << "\n\n";
    	array_size = 10;
    	
    	int array1[array_size];
    	p1 = array1;

    	for(int i=0; i<array_size; i++)
    		*(p1+i) = pow(2,i);

    	int array2[array_size];
    	p2 = array2;

    	for(int i=0; i<array_size; i++)
    		*p2 = *p1;

    	// Repeat part 10-12 with vectors
    	cout << "\n\n";
    	vector<int> v1;

    	for(int i=0; i<array_size; i++)
    		v1.push_back(pow(2,i));

    	vector<int> v2 = v1;

    	for(int num : v2)
    		cout << num << ' ';

    	cout << '\n';
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

void print_array10(ostream& os, int* a){
	for(int i=0; i<10; i++)
		os << *(a+i) << ' ';
}

void print_array(ostream& os, int* a, int n){
	for(int i=0; i<n; i++)
		os << *(a+i) << ' ';
}

void print_vector(ostream&os, vector<int> v){
	for(int num : v)
		os << num << ' ';
}
