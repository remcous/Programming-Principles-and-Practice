/****************************************
*Binary Calculator program from Chapter 6
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
    int value;     // for numbers: a value
    Token(char ch)    // make a Token from a char
            :kind(ch), value(0) { }
    Token(char ch, int val)     // make a Token from a char and a double
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

void print_binary(int value);   // Print out bits of an integer
int expression();   // Deal with '|'
int tertiary();     // Deal with '^'
int secondary();    // Deal with '&'
int primary();      // Deal with numbers and parenthesis

/****************************************
*           GLOBAL VARIABLES
****************************************/

#define NUMBER '8'
#define NUM_BYTES 1
#define BITS_PER_BYTE 8
#define BYTES_PER_INT (sizeof(int)/sizeof(char))
#define QUIT 'q'
#define EQUAL '='
Token_stream ts;    // Global Token stream

/****************************************
*             MAIN FUNCTION
****************************************/

int main(){
    //std::cin.unsetf(std::ios::dec);
    //std::cin.unsetf(std::ios::hex);
    try{
        int val = 0;
        while(cin){
            Token t = ts.get();

            if(t.kind == QUIT) break;    // 'q' for quit
            if(t.kind == EQUAL)           // '=' for print now
                cout << hex << val << '\n';
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

void print_binary(int value) {
    constexpr short bits = BITS_PER_BYTE * NUM_BYTES;

    for(int i=bits; i>0; i--){
        if(i%BITS_PER_BYTE == 0 && i!=bits) cout << ' ';
        (value & (0x01 << (i-1))) ? cout << '1' : cout << '0';
    }
}

int expression(){
    int left = tertiary();
    Token t = ts.get();

    while(true){
        switch(t.kind){
            case '|':   // deal with '|'
                left = left | tertiary();
                t = ts.get();
                break;
            default:
                ts.putback(t);
                return left;
        }
    }
}

int tertiary(){
    int left = secondary();
    Token t = ts.get();

    while(true){
        switch(t.kind){
            case '^':   // deal with '^'
                left = left ^ secondary();
                t = ts.get();
                break;
            default:
                ts.putback(t);
                return left;
        }
    }
}

int secondary(){
    int left = primary();
    Token t = ts.get();

    while(true){
        switch(t.kind){
            case '&':   // deal with '&'
                left = left & primary();
                t = ts.get();
                break;
            default:
                ts.putback(t);
                return left;
        }
    }
}

int primary(){
    Token t = ts.get();
    if(t.kind == '!'){  // deal with NOT
        int d = expression();
        return !d;
    }else if(t.kind == '~'){    // Find the complement
        int d = expression();
        return ~d;
    }

    switch(t.kind){
        case '(':   // Handle '(' expression ')'
        {
            int d = expression();
            t = ts.get();
            if(t.kind != ')') error("')' expected");
            break;
        }
        case NUMBER:
            return t.value; // return the number value
        default:
            error("Primary expected");
    }
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
        case EQUAL:   // for print
        case QUIT:   // for quit
        case '!': case '~':
        case '(': case ')': case '&': case '|': case '^':
            return Token{ch};   // let each character represent itself
        case '0': case '1': case '2': case '3': case '4':
        case '5': case '6': case '7': case '8': case '9':
        case 'A': case 'B': case 'C': case 'D': case 'E':
        case 'F': case 'a': case 'b': case 'c': case 'd':
        case 'e': case 'f':
        {
            cin.putback(ch);        // put digit back into the input stream
            int val;
            cin >> hex >> val;             // read an integer number
            return Token(NUMBER,val);  // let NUMBER represent "a number"
        }
        default:
            error("Bad token");
    }
}

