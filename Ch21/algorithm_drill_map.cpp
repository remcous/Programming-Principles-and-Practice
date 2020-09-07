/*
    algorithm_drill_map.cpp

    Revision History:
*/

#include <iostream>
#include <fstream>
#include <map>
#include <iomanip>
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

/****************************************
*             MAIN FUNCTION
****************************************/

int main(){
    try{
        map<string, int> msi;

        msi["Matthews"] = 34;
        msi["Tavares"] = 91;
        msi["Marner"] = 16;
        msi["Nylander"] = 88;
        msi["Hyman"] = 11;
        msi["Rielly"] = 44;
        msi["Muzzin"] = 8;
        msi["Sandin"] = 38;
        msi["Dermott"] = 23;
        msi["Andersen"] = 31;

        for(auto a = msi.begin(); a != msi.end(); a++)
        {
        	cout << setw(10) << a->first << ' ' 
        		<< setw(2) << a->second << endl;
        }

        cout << "\nErasing all elements...\n"; 

        for(auto a = msi.begin(); a != msi.end(); a++)
        {
        	msi.erase(a);
        }

        cout << "Printing map contents:\n";
        for(auto a = msi.begin(); a != msi.end(); a++)
        {
        	cout << setw(10) << a->first << ' ' 
        		<< setw(2) << a->second << endl;
        }
        cout << "End of map contents\n";

        string s = "";
        int num = 0;

        cout << "\nPlease enter 10 string integer pairs of values (ie, Matthews 34):\n";

        for(int i=0; i<10; i++)
        {
        	cin >> s >> num;
        	msi[s] = num;
        }

        cout << "\nPrinting contents...\n";

        for(auto a = msi.begin(); a != msi.end(); a++)
        {
        	cout << setw(10) << a->first << ' ' 
        		<< setw(2) << a->second << endl;
        }

        cout << "The sum of the entered values is: "
        	<< accumulate(msi.begin(), msi.end(), 0, 
        		[](int value, const map<string, int>::value_type& m)
        		{return value + m.second;}) << endl;

        cout << "\nCreating a new map <int, string>...\n";

        map<int, string> mis;

        for(auto a = msi.begin(); a != msi.end(); a++)
        {
        	mis[a->second] = a->first;
        }

        cout << "\nPrinting contents...\n";

        for(auto a = mis.begin(); a != mis.end(); a++)
        {
        	cout << setw(2) << a->first << ' ' 
        		<< setw(10) << a->second << endl;
        }
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