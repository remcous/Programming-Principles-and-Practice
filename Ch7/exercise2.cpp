/*
    Simple Calculator

    Revision History:
        Added variable support - Remi Coussement July 2020
        Revised by Remi Coussement July 2020
        Originally written by Bjarne Stroustrup Spring 2004

    This program implements a basic expression calculator.
    Input from cin; output to cout
    The grammar for input is:

    Calculation:
        Statement
        Print
        Quit
        Calculation Statement

    Statement:
        Declaration
        Expression

    Declaration:
        "let" name "=" Expression

    Print:
        ;

    Quit:
        q

    Expression:
        Term
        Expression + Term
        Expression - Term

    Term:
        Primary
        Term * Primary
        Term / Primary
        Term % Primary

    Primary:
        Number
        ( Expression )
        - Primary
        + Primary

    Number:
        Floating-point literal

    Input comes from cin through Token_stream called ts
*/

#include "../std_lib_facilities.h"

/****************************************
*           CLASS DEFINITIONS
****************************************/

class Token {
public:
    char kind;          // what kind of token
    double value;       // for numbers: a value 
    string name;        
    Token() : kind{0} {}
    Token(char ch)      // make a Token from a char
        :kind(ch), value(0) { }    
    Token(char ch, double val)     // make a Token from a char and a double
        :kind(ch), value(val) { }
    Token(char ch, string n): kind{ch}, name{n} {}
};

class Token_stream{
public:
    Token_stream();         // make a Token_stream that reads from cin
    Token get();            // get a Token
    void putback(Token t);  // put a Token back
    void ignore(char c);    // discard characters up to and include a c
private:
    bool full = false;       // is there a Token in the buffer?
    Token buffer;           // here is where we keep a Token put back using putback()
};

class Variable{
public:
    string name;
    double value;
    Variable(string n, double v) : name{n}, value{v} {};
};

/****************************************
*           FUNCTION PROTOTYPES
****************************************/

double expression();    // deal with + and -
double term();          // deal with *, /, and %
double primary();       // deal with numbers and parentheses
void calculate();       // expression evaluation loop
void clean_up_mess();   // error recovery to continue operation cleanly
double get_value(string s); // return the value of the Variable named s
void set_value(string s, double d); // set the variable named s to d
double statement();     // deal with declaration and expressions
bool is_declared(string var);   // is var already in var_table?
double define_name(string var, double val); // add {var, val} to var_table
double declaration();   // declare variables and store in var_table

/****************************************
*           GLOBAL VARIABLES
****************************************/

Token_stream ts;    // Global Token stream
vector<Variable> var_table;
const char number = '8';    // t.kind==number means that t is a number Token
const char quit = 'q';      // t.kind==quit means that t is a quit Token
const char print = ';';     // t.kind==print means that t is a print Token
const string prompt = "> ";
const string result = "= "; // used to indicate that what follows is a result
const char name = 'a';      // name Token
const char let = 'L';       // declaration Token
const string declkey = "let";    // declaration keyword

/****************************************
*             MAIN FUNCTION
****************************************/

int main(){
    try{
        // predefine names:
        define_name("pi", 3.1415926535);
        define_name("e", 2.7182818284);

        calculate();
        keep_window_open("~~"); // cope with Windows console mode
        return 0;
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
}

/****************************************
*       FUNCTION DEFINITIONS - GLOBAL
****************************************/

double statement(){
    Token t = ts.get();
    switch(t.kind){
    case let:
        return declaration();
    default:
        ts.putback(t);
        return expression();
    }
}

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
        case '%':
        {
            double d = primary();
            if(d == 0) error("%: divide by zero");
            left = fmod(left,d);
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
    switch(t.kind){
    case '(':   // Handle '(' expression ')'
    {
        double d = expression();
        t = ts.get();
        if(t.kind != ')') error("')' expected");
        return d;
    }
    case number:
        return t.value; // return the number's value
    case name:
    	return get_value(t.name);	// return teh variable's value
    case '-':
        return - primary();
    case '+':
        return primary();
    default:
        error("primary expected");
    }
}

void calculate(){
    while(cin){
        try{
            cout << prompt;
            Token t = ts.get();
            while(t.kind == print) t=ts.get();  // first discard all prints
            if(t.kind == quit) return;          // quit
            ts.putback(t);
            cout << result << statement() << '\n';
        }
        catch(exception& e){
            cerr << e.what() << '\n';           // write error message
            clean_up_mess();
        }
    }
}

void clean_up_mess(){   // naive
    ts.ignore(print);
}

double get_value(string s){
    for(const Variable& v : var_table)
        if(v.name == s) return v.value;
    error("get: undefined variable ", s);
}

void set_value(string s, double d){
    for(Variable& v : var_table)
        if(v.name == s){
            v.value = d;
            return;
        }
    error("set: undefined variable ", s);
}

bool is_declared(string var){
    for(const Variable &v : var_table)
        if(v.name == var) return true;
    return false;
}

double define_name(string var, double val){
    if(is_declared(var)) error(var, " declared twice");
    var_table.push_back(Variable{var, val});
    return val;
}

double declaration(){
    // assume we have seen "let"
    // handle: name = expression
    // declare a variable called "name" with the initial value "expression"
    Token t = ts.get();
    if(t.kind != name) error("name expected in declaration");
    string var_name = t.name;

    Token t2 = ts.get();
    if(t2.kind != '=') error("= missing in declaration of ", var_name);

    double d = expression();
    define_name(var_name, d);
    return d;
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
    case print: // for print
    case quit:  // for quit
    case '(':
    case ')':
    case '+':
    case '-':
    case '*':
    case '/':
    case '%':
    case '=':
        return Token{ch};   // let each character represent itself
    case '.':
    case '0': case '1': case '2': case '3': case '4':
    case '5': case '6': case '7': case '8': case '9':   // numeric literal
    {
        cin.putback(ch);        // put digit back into the input stream
        double val;
        cin >> val;             // read a floating-point number
        return Token(number,val);
    }
    default:
        if(isalpha(ch)){
            string s;
            s += ch;
            while(cin.get(ch)&&(isalpha(ch)||isdigit(ch)||ch=='_')) s+=ch;
            cin.putback(ch);
            if(s == declkey) return Token{let}; // declaration keyword
            return Token{name, s};
        }
        error("Bad token");
    }
}

void Token_stream::ignore(char c){
    // c represents the kind of Token
    // first look in the buffer:
    if(full && c==buffer.kind){
        full = false;
        return;
    }
    full = false;

    // now search input:
    char ch = 0;
    while(cin >> ch)
        if(ch == c) return;
}