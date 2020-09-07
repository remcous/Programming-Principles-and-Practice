/*
    algorithm_drill_vector.cpp

    Revision History:
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

/****************************************
*           CLASS DEFINITIONS
****************************************/

/****************************************
*           FUNCTION PROTOTYPES
****************************************/

/****************************************
*           GLOBAL VARIABLES
****************************************/

const string FILENAME = "input2.txt";

/****************************************
*             MAIN FUNCTION
****************************************/

int main(){
    try{
        ifstream ifs{FILENAME};

        if(!ifs) throw exception();

        vector<double> vd;

       	double temp;

       	while(ifs >> temp)
       		vd.push_back(temp);

       	for(double temp : vd)
       		cout << temp << ' ';

       	cout << endl;

       	vector<int> vi;

       	for(int i=0; i<vd.size(); i++)
       		vi.push_back(vd[i]);

       	for(int i=0; i<vd.size(); i++)
       	{
       		cout << vi[i] << '\t' << vd[i] << endl;
       	}

       	cout << "Sum of vd elements: " 
       		<< accumulate(vd.begin(), vd.end(), 0.0) << endl;

       	cout << "Sum of vi elements: " 
       		<< accumulate(vi.begin(), vi.end(), 0.0) << endl;

       	cout << "Difference is: "
       		<< accumulate(vd.begin(), vd.end(), 0.0) -
       		accumulate(vi.begin(), vi.end(), 0.0) << endl;

       	cout << "Reversing elements of vd...\n";
       	reverse(vd.begin(), vd.end());

       	for(double temp : vd)
       		cout << temp << ' ';
       	cout << endl;

       	double mean = accumulate(vd.begin(), vd.end(), 0.0) / vd.size();

       	cout << "The mean of the values in vd is: " << mean << endl;

       	vector<double> vd2;

       	cout << "Filling vd2 with values below the mean...\n";

       	for(double temp : vd)
       	{
       		if(temp < mean) vd2.push_back(temp);
       	}

       	cout << "Printing contents of vd2...\n";
       	for(double temp : vd2)
       		cout << temp << ' ';
       	cout << endl;

       	cout << "\nSorting the contents of vd...\n";

       	sort(vd.begin(), vd.end());

       	for(double temp : vd)
       		cout << temp << ' ';
       	cout << endl;
    }
    catch(exception& e){
        cerr << e.what() << '\n';
        return 1;
    }
    catch(...){
        cerr << "exception\n";
        return 2;
    }
    return 0;
}

/****************************************
*       FUNCTION DEFINITIONS - GLOBAL
****************************************/