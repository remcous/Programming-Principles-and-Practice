/*
    container_drill.cpp

    Revision History:
*/

#include "../Libraries/std_lib_facilities.h"

/****************************************
*           CLASS DEFINITIONS
****************************************/

/****************************************
*           FUNCTION PROTOTYPES
****************************************/

namespace my_copy
{
	template <typename Iter1, typename Iter2>
		// requires Input_iterator<Iter1>() && Output_iterator<Iter2>()
	Iter2 copy(Iter1 f1, Iter1 e1, Iter2 f2);
}

/****************************************
*           GLOBAL VARIABLES
****************************************/

/****************************************
*             MAIN FUNCTION
****************************************/

int main(){
    try{
        array<int,10> arr{0,1,2,3,4,5,6,7,8,9};
        vector<int> vect{0,1,2,3,4,5,6,7,8,9};
        list<int> lst{0,1,2,3,4,5,6,7,8,9};

        auto arr2 = arr;
        vector<int> vect2{vect};
        list<int> lst2{lst};

        for(auto i=arr.begin(); i!=arr.end();i++)
        	*i *= 2;

        for(auto i=vect.begin(); i!=vect.end();i++)
        	*i *= 3;
        
        for(auto i=lst.begin(); i!=lst.end();i++)
        	*i *= 5;
        
        // copy array into vector
        my_copy::copy(arr.begin(), arr.end(), vect.begin());

        // copy list into array
        my_copy::copy(lst.begin(), lst.end(), arr.begin());

        for(auto i=lst.begin(); i != lst.end(); i++)
        	cout << *i << ' ';
        cout << endl;

        auto loc = find(vect.begin(), vect.end(), 3);

        if(loc == vect.end())
        	cout << "The value 3 was not found in the vector.\n";
        else{
        	int i=0;
        	for(auto j = vect.begin(); j != loc; j++)
        	{
        		i++;
        	}

        	cout << "The value 3 was found in the vector at position " << i << "!\n";
        }
        auto loc2 = find(lst.begin(), lst.end(), 27);

        if(loc2 == lst.end())
        	cout << "The value 27 was not found in the list.\n";
        else
        {
        	int i=0;
        	for(auto j = lst.begin(); j != loc2; j++)
        	{
        		i++;
        	}

        	cout << "The value 27 was found in the list at position " << i << "!\n";
        }
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

template <typename Iter1, typename Iter2>
	// requires Input_iterator<Iter1>() && Output_iterator<Iter2>()
Iter2 my_copy::copy(Iter1 f1, Iter1 e1, Iter2 f2)
{
	if(f1 == e1) return f2;	// no elements to copy

	while(f1 != e1)
	{
		*f2 = *f1;
		f2++;
		f1++;
	}

	return f2;
}
