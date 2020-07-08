/****************************************
*   Calculator program from Chapter 6
* of Programming Principles and Practices
*      with C++ by Bjarne Stroustrup
****************************************/

#include "../std_lib_facilities.h"

/****************************************
*           CLASS DEFINITIONS
****************************************/

class Token {
public:
    char kind;        // what kind of token
    double value;     // for numbers: a value 
    Token(char ch)    // make a Token from a char
        :kind(ch), value(0) { }    
    Token(char ch, double val)     // make a Token from a char and a double
        :kind(ch), value(val) { }
};

class Token_stream{
public:
    Token_stream();         // make a Token_stream that reads from cin
    Token get();            // get a Token
    void putback(Token t);  // put a Token back
private:
    bool full = false;       // is there a Token in the buffer?
    Token buffer;           // here is where we keep a Token put back using putback()
};

/****************************************
*           FUNCTION PROTOTYPES
****************************************/

double factorial(double d); // handle factorial calculations
double expression();    // deal with + and -
double term();          // deal with *, /, and %
double primary();       // deal with numbers and parentheses

/****************************************
*           GLOBAL VARIABLES
****************************************/

Token_stream ts;    // Global Token stream

/****************************************
*             MAIN FUNCTION
****************************************/

int main(){
    try{
        double val = 0;
        while(cin){
            Token t = ts.get();

            if(t.kind == 'q') break;    // 'q' for quit
            if(t.kind == '=')           // ';' for print now
                cout << "=" << val << '\n';
            else
                ts.putback(t);
            val = expression();
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
}

/****************************************
*       FUNCTION DEFINITIONS - GLOBAL
****************************************/

double expression(){
    double left = term();       // read and evaluate as a Term
    Token t = ts.get();         // get the next token from Token_stream

    while(true){
        switch(t.kind){
        case '+':
            left += term();     // evaluate Term and add
            t = ts.get();
            break;
        case '-':
            left -= term();     // evaluate Term and subtract
            t = ts.get();
            break;
        default:
            ts.putback(t);      // put t back into the token stream
            return left;        // finally: no more + or -; return the answer
        }
    }
}

double term(){
    double left = primary();
    Token t = ts.get();         // get the next token from Token stream
    while(true){
        switch(t.kind){
        case '*':
            left *= primary();
            t = ts.get();
            break;
        case '/':
        {
            double d = primary();
            if(d == 0) error("divide by zero");
            left /= d;
            t = ts.get();
            break;
        }
        default:
            ts.putback(t);      // put t back into the Token stream
            return left;
        }
    }
}

double primary(){
    Token t = ts.get();
    double d=0;
    switch(t.kind){
    case '(':   // Handle '(' expression ')'
        d = expression();
        t = ts.get();
        if(t.kind != ')') error("')' expected");
        break;
    case '{':
        d = expression();
        t = ts.get();
        if(t.kind != '}') error("'}' expected");
        break;
    case '+':
        d = primary();
        break;
    case '-':
        d = -primary();
        break;
    case '8':           // we use '8' to represent a number
        return t.value; // return the number's value
    default:
        error("primary expected");
    }

    // Check for factorial (!) following
    t = ts.get();
    if(t.kind != '!'){
        ts.putback(t);
        return d;
    }
    return factorial(d);
}

double factorial(double d){
    int i = d;
    if(i != d) error ("Factorial not defined for non-integers");
    if(i < 0) error ("Factorial not defined for negative values");
    if(i > 31) error("Factorial is too large for integer type");
    int res = 1;
    for(i; i>1; i--) res *= i;
    return res;
}

/****************************************
*   FUNCTION DEFINITIONS - TOKEN_STREAM
****************************************/

Token_stream::Token_stream():full(false),buffer(0)  // no token in buffer
{}

void Token_stream::putback(Token t){
    if(full) error("putback() into a full buffer");
    buffer = t;     // copy t to buffer
    full = true;    // buffer is now full
}

Token Token_stream::get(){
    if(full){           // do we already have a Token ready?
        full = false;   // remove Token from buffer
        return buffer;
    }

    char ch;
    cin >> ch;          // note that >> skips whitespace(space, newline, tab, etc)

    switch(ch){
    case '=':   // for print
    case 'q':   // for quit
    case '{': case '}':
    case '(': case ')': case '+': case '-': case '*': case '/': case '!':
        return Token{ch};   // let each character represent itself
    case '.':
    case '0': case '1': case '2': case '3': case '4':
    case '5': case '6': case '7': case '8': case '9':
    {
        cin.putback(ch);        // put digit back into the input stream
        double val;
        cin >> val;             // read a floating-point number
        return Token('8',val);  // let '8' represent "a number"
    }
    default:
        error("Bad token");
    }
}