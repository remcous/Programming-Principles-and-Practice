/*
    algorithm_drill.cpp

    Revision History:
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <algorithm>

using namespace std;

/****************************************
*           CLASS DEFINITIONS
****************************************/

struct Item
{
	string name;
	int iid;
	double value;
};

/****************************************
*           FUNCTION PROTOTYPES
****************************************/

istream& operator>>(istream& is, Item& a);
ostream& operator<<(ostream& os, const Item& a);

void print_all(vector<Item>& vi);

/****************************************
*           GLOBAL VARIABLES
****************************************/

const string fName = "input.txt";

/****************************************
*             MAIN FUNCTION
****************************************/

int main(){
    try{
        ifstream ifs{fName};

        if(!ifs) throw exception();

        Item temp;
        vector<Item> vi;

        while(ifs >> temp)
        {
        	vi.push_back(temp);
        }

        ifs.close();

        cout << "vi.size() = " << vi.size() << endl;
        cout << "Initial order: \n";
        print_all(vi);

        // name sort
        std::sort(vi.begin(), vi.end(),
        	[](const Item& a, const Item& b){
        		return a.name < b.name;
        	});

     	cout << "\nSorting by Name: \n";
        print_all(vi);

        // iid sort
        std::sort(vi.begin(), vi.end(),
        	[](const Item& a, const Item& b){
        		return a.iid < b.iid;
        	});

     	cout << "\nSorting by Item id: \n";
        print_all(vi);

        // value sort
        std::sort(vi.begin(), vi.end(),
        	[](const Item& a, const Item& b){
        		return a.value > b.value;
        	});

     	cout << "\nSorting by Value (descending): \n";
        print_all(vi);

        cout << "\nInserting {horse shoe, 99, 12.34}\n";
        vi.push_back({"horse shoe", 99, 12.34});
        cout << "Inserting {Canon S400, 9988, 499.95}\n";
        vi.push_back({"Canon S400", 9988, 499.95});

        print_all(vi);

        cout << "\n\nErasing Dermott by name...\n";
        vi.erase(find_if(vi.begin(), vi.end(), [](const Item& a){return a.name == "Dermott";}));
        cout << "Erasing Andersen by name...\n\n";
        vi.erase(find_if(vi.begin(), vi.end(), [](const Item& a){return a.name == "Andersen";}));

        print_all(vi);

        cout << "\n\nErasing 16 by Item id...\n";
        vi.erase(find_if(vi.begin(), vi.end(), [](const Item& a){return a.iid == 16;}));
        cout << "Erasing 11 by Item id...\n\n";
        vi.erase(find_if(vi.begin(), vi.end(), [](const Item& a){return a.iid == 11;}));

        print_all(vi);
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

istream& operator>>(istream& is, Item& a)
{
	is >> a.name >> a.iid >> a.value;
	return is;
}

ostream& operator<<(ostream& os, const Item& a)
{
	os << setw(10) << a.name << ' ' 
		<< setw(2) << a.iid << ' ' 
		<< setw(11) << fixed << setprecision(2) << a.value;
	return os;
}

void print_all(vector<Item>& vi)
{
	for(Item item : vi)
	{
		cout << item << endl;
	}
}
