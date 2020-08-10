/*
    exercise7.cpp

    Revision History:
*/

#include <iostream>
#include <string>

using namespace std;

/****************************************
*             MAIN FUNCTION
****************************************/

int main(){
    try{
    	// using c_string and pointers

        cout << "Enter a string: using ! to indicate the end\n";

        char ch;
        int array_size = 1;
        char* array = new char[array_size];
        *array = 0;

        cin.clear();
        fflush(stdin);

        // have to manually assign more memory to array
        while(cin.get(ch) && ch != '!'){
        	array_size++;
        	char* temp = new char[array_size];

        	for(int i=0; i < array_size; i++){
        		if(i == array_size-1) temp[i] = 0;
        		else if(i == array_size-2) temp[i] = ch;
        		else{
        			temp[i] = array[i];
        		}
        	}

        	delete[] array;
        	array = temp;
        }

        cout << array << endl;

        delete[] array;

        // using string
        cout << "\nEnter a string: using ! to indicate the end\n";

        string result = "";

        cin.clear();
        fflush(stdin);

        // string automatically assigns freestore memory as needed
        while(cin.get(ch) && ch != '!'){
        	result.append(&ch);
        }

        cout << result << endl;
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