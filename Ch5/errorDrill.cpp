#include "../std_lib_facilities.h"

int main(){
try{
    // Cout << "Success!\n"; // 1
    // cout << "Success!\n; // 2
    // string res="7"; vector<int> v(10); v[5] = stoi(res); cout << "Success!\n"; // 5
    string s = "Success!\n";
    for(int i=0; i<=11; ++i) cout << s[i]; // 18
    keep_window_open();
    return 0;
}
catch(exception& e){
    cerr << "error: " << e.what() << '\n';
    keep_window_open();
    return 1;
}
catch(...){
    cerr << "Oops: unknown exception!\n";
    keep_window_open();
    return 2;
}
}