#include "../std_lib_facilities.h"

double ctok(double c)   // converts Celsius to Kelvin
{
    int k = c + 273.15;
    return k;
}

int main(){
    double c = 0;       // declare input variable
    cin >> c;           // retrieve temperature to input variable
    if(c < -273.15){
        cerr << "Error: temperature is invalid\n";
        return 1;
    }
    double k = ctok(c); // convert temperature
    cout << k << '\n';  // print out temperature

    return 0;
}