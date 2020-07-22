#include "../std_lib_facilities.h"

int main(){
	string iname;

	cout << "Enter the name of the file to open: ";
	cin >> iname;
	try{
		ifstream ist{iname};
		if(!ist) error("Can't open file: ", iname);

		int sum = 0;

		for(int num; ist >> num;){
			sum += (int)num;
		}
		if(!ist.eof()) error("File contains non-integer data: ", iname);
		if(ist.fail()) ist.clear();

		cout << "The sum of the file contents is " << sum << '\n';
	}catch(exception& e){
		cerr << e.what() << '\n';
		return 1;
	}
	return 0;
}