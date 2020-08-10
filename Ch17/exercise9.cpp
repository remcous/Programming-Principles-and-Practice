/*
    exercise9.cpp

    Revision History:
*/

#include "../std_lib_facilities.h"

/****************************************
*             MAIN FUNCTION
****************************************/

int main(){
    try{
        // Test the direction of stack growth
        int num1 = 0;
        int num2 = 0;
        int num3 = 0;

        cout << "Addresses for stack allocation:\n" << &num1
        	<< '\n' << &num2 << '\n' << &num3 << "\n\n";

        if(&num2 > &num1) cout << "Stack grows upwards\n\n";
        else cout << "Stack grows downwards\n\n";

        // Test direction of heap growth
        int *ip1 = new int{0};
        int *ip2 = new int{0};
        int *ip3 = new int{0};

        cout << "Addresses for heap allocation:\n" << ip1
        	<< '\n' << ip2 << '\n' << ip3 << "\n\n";

        if(ip2 > ip1) cout << "Heap grows upwards\n";
        else cout << "Heap grows downwards\n";

        delete ip1;
        delete ip2;
        delete ip3;
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
