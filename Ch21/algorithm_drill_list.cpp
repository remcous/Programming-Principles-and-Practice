/*
    algorithm_drill_list.cpp

    Revision History:
*/

#include <iostream>
#include <fstream>
#include <list>
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

template<typename Iter>
void print_all(Iter start, Iter end);

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
        vector<Item> li;

        while(ifs >> temp)
        {
        	li.push_back(temp);
        }
        
        ifs.close();

        cout << "Initial order: \n";
        print_all(li.begin(), li.end());
        
        // name sort
        std::sort(li.begin(), li.end(),
        	[](const Item& a, const Item& b){
        		return a.name < b.name;
        	});

        
     	cout << "\nSorting by Name: \n";
        print_all(li.begin(), li.end());
        
        // iid sort
        std::sort(li.begin(), li.end(),
        	[](const Item& a, const Item& b){
        		return a.iid < b.iid;
        	});

     	cout << "\nSorting by Item id: \n";
        print_all(li.begin(), li.end());

        // value sort
        std::sort(li.begin(), li.end(),
        	[](const Item& a, const Item& b){
        		return a.value > b.value;
        	});

     	cout << "\nSorting by Value (descending): \n";
        print_all(li.begin(), li.end());
        
        cout << "\nInserting {horse shoe, 99, 12.34}\n";
        li.push_back({"horse shoe", 99, 12.34});
        cout << "Inserting {Canon S400, 9988, 499.95}\n";
        li.push_back({"Canon S400", 9988, 499.95});

        print_all(li.begin(), li.end());
        
        cout << "\n\nErasing Dermott by name...\n";
        li.erase(find_if(li.begin(), li.end(), [](const Item& a){return a.name == "Dermott";}));
        cout << "Erasing Andersen by name...\n\n";
        li.erase(find_if(li.begin(), li.end(), [](const Item& a){return a.name == "Andersen";}));

        print_all(li.begin(), li.end());

        cout << "\n\nErasing 16 by Item id...\n";
        li.erase(find_if(li.begin(), li.end(), [](const Item& a){return a.iid == 16;}));
        cout << "Erasing 11 by Item id...\n\n";
        li.erase(find_if(li.begin(), li.end(), [](const Item& a){return a.iid == 11;}));

        print_all(li.begin(), li.end());
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
		<< setw(4) << a.iid << ' ' 
		<< setw(11) << fixed << setprecision(2) << a.value;
	return os;
}

template <typename Iter>
void print_all(Iter start, Iter end)
{
	while(start != end)
    {
        cout << *start << endl;
        start++;
    }
}
