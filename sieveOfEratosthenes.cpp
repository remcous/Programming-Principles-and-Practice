#include "std_lib_facilities.h"

#define MAX_NUM 100

int main(){
    bool numbers[MAX_NUM + 1];

    numbers[0] = false;
    numbers[1] = false;

    for(int i=2; i<=MAX_NUM; i++){
        numbers[i] = true;
    }

    for(int i=2; i<=MAX_NUM; i++){
        if(!numbers[i]) continue;
        
        for(int j=i*2; j<=MAX_NUM; j+=i){
            numbers[j] = false;
        }
    }

    for(int i=2; i<=MAX_NUM; i++){
        if(numbers[i]) cout << i << ' ';
    }

    cout << endl;
    return 0;
}