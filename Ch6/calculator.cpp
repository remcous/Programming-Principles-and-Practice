/****************************************
*   Calculator program from Chapter 6
* of Programming Principles and Practices
*      with C++ by Bjarne Stroustrup
****************************************/

#include "../std_lib_facilities.h"

int main(){
    cout << "Please enter expression (we can handle +,-,*, and /)\n";
    cout << "Add an x to end expression (e.g., 1+2*3x): ";
    int lval = 0;
    int rval;
    cin >> lval;    // Read leftmost operand
    
    if(!cin) error("No first operand");

    for(char op; cin>>op;){  // Read operator and right-hand operand
                            // repeatedly
        if(op!='x') cin >> rval;
        if(!cin) error("No second operand");
        switch(op){
        case '+':
            lval += rval;   // add: lval = lval + rval
            break;
        case '-':
            lval -= rval;   // subtract: lval = lval - rval
            break;
        case '*':
            lval *= rval;   // multiply: lval = lval * rval
            break;
        case '/':
            lval /= rval;   // divide: lval = lval / rval
            break;
        default:            // Not another operator: print result
            cout << "Result: " << lval << '\n';
            keep_window_open();
            return 0;
        }
    }
    error("Bad expression");
}