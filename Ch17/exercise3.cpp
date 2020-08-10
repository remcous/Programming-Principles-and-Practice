/*
    exercise3.cpp

    Revision History:
*/

#include <iostream>

using namespace std;

/****************************************
*           CLASS DEFINITIONS
****************************************/

/****************************************
*           FUNCTION PROTOTYPES
****************************************/

void to_lower(char* s);
char* strdup(const char*);
const char* findx(const char* s, const char* x);

/****************************************
*           GLOBAL VARIABLES
****************************************/

/****************************************
*             MAIN FUNCTION
****************************************/

int main(){
    try{
    	// exercise 3
        char text[]{"HELLO WORLD!!.@#hello world102"};

        to_lower(text);

        cout << text << endl; 

        // exercise 4

        char* text2 = strdup(text);

        cout << text2 << endl;

        delete[] text2;

        // exercise 5

        const char* result = findx(text, "world1");

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

// convert uppercase to lowercase in a c_string using pointers
void to_lower(char* s){
	int i = 0;
	while(*(s+i) != '\0'){
		if(*(s+i) >= 65 && *(s+i) <= 90){
			*(s+i) += 32;
		}

		i++;
	}
}

// copy a c_string and assign to new free-store memory
char* strdup(const char* s){
	// find number of characters in string
	int count = 0;
	while(*(s+count) != '\0') count++;

	// create a new c string
	char* copy = new char[count];

	// copy characters one by one to new string
	for(int i=0; i<count; i++){
		copy[i] = *(s + i);
	}

	return copy;
}

// find first occurence of substring x in string s
//return pointer to start of substring in main string
const char* findx(const char* s, const char* x){
	if(x == nullptr || s == nullptr) return nullptr;// no substring or main string
	if(*x == '\0' || *s == '\0') return nullptr;	// empty substring or string

	for(int i=0; *(s+i); i++){					// loop through main string
		if(*(s+i) == *x){						// potential match
			for(int j=1; *(x+j); j++){			// loop through substring
				if(*(s+i+j) != *(x+j)) break;	// does not match substring
				if(*(x+j+1) == 0) return &s[i];
				if(*(s+i+j+1) == 0) return nullptr;	// s ended before substring
			}
		}
	}

	return nullptr;		// no match found
}
