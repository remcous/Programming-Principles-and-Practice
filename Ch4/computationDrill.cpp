#include "../std_lib_facilities.h"

// No magic numbers: conversion factors
constexpr double CM_TO_M = 1.0/100;
constexpr double IN_TO_M = 2.54 * CM_TO_M;
constexpr double FT_TO_M = 12 * IN_TO_M;

int main(){
    // input variables
    double number;
    string unit;
    vector<double> numbers;

    // analytics of numbers
    double largest, smallest, sum=0;
    int count = 0;

    // flag to initialize the largest and smallest values
    bool first_run = true;

    cout << "Enter a measurement: ";

    while(cin >> number >> unit){
        // unit check and conversion
        if(unit == "m");
        else if(unit == "cm"){
            number *= CM_TO_M;
        }else if(unit == "in"){
            number *= IN_TO_M;
        }else if(unit == "ft"){
            number *= FT_TO_M;
        }else{  // error handling
            cout << "Sorry, I don't know the unit: " << unit << endl;
            cout << "Enter a measurement: ";
            continue;
        }

        // output the number in terms of meters
        cout << number << "m";
        count++;
        sum += number;
        numbers.push_back(number);

        // handle special case of first run
        if(first_run){
            largest = number;
            smallest = number;
            first_run = false;
        }

        // check for new largest or smallest value
        if(number > largest){
            cout << " the largest so far";
            largest = number;
        }

        if (number < smallest){
            cout << " the smallest so far";
            smallest = number;
        }

        cout << endl;
        cout << "Enter a measurement: ";
    }

    cout << "\n\n";

    sort(numbers);

    for(double num : numbers){
        cout << num << endl;
    }

    if(count > 0){
        cout << "\n\nThe largest value is: " << largest << "m\n";
        cout << "The smallest value is " << smallest << "m\n";
        if(count > 1){
            cout << "The " << count 
                << " numbers sum up to " << sum << "m\n";
        }
        else{
            cout << "The number is " << sum << "m\n";
        }
    }
}