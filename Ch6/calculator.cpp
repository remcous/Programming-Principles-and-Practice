/****************************************
*   Calculator program from Chapter 6
* of Programming Principles and Practices
*      with C++ by Bjarne Stroustrup
****************************************/

#include "../std_lib_facilities.h"

int main(){
    cout << "Please enter expression (we can handle + and -): ";
    int lval = 0;
    int rval;
    char op;
    int res;

    cin >> lval >> op >> rval;  // reads something like 1 + 3

    if(op == '+') 
        res = lval + rval;
    else if (op == '-')
        res = lval - rval;

    cout << "Result: " << res << '\n';
    keep_window_open();

    return 0;
}