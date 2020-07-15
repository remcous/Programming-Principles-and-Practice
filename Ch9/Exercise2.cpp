/******************************************************
*	Exercise 2: design and implement a name_pair class
*	By: Remi Coussement
*	Rev:
*		
******************************************************/
#include "../std_lib_facilities.h"

#define INT_MAX sizeof(int)/sizeof(char)*8

/**********************************
*		  CLASS DEFINITION
**********************************/

class Name_pairs{
public:
	void read_names();
	void read_ages();
	void print();
	void sort();
	Name_pairs(){}
private:
	vector<string> name;
	vector<double> age;
};

/**********************************
*			MAIN PROGRAM
**********************************/

int main(){
	try{
		Name_pairs np;

		np.read_names();
		np.read_ages();

		cout << "First order:\n";
		np.print();

		np.sort();
		cout << "\n\nSorted order:\n";
		np.print();

		return 0;
	}catch(exception& e){
		cerr << "Error: " << e.what() << "\n";
		return 1;
	}catch(...){
		cerr << "Oops: Unknown exception\n";
		return 2;
	}
}

/**********************************
*		   MEMBER FUNCTIONS
**********************************/

void Name_pairs::read_names(){
	string temp;
	std::cout << "Enter space separated names type 'done' when finished:\n";
	while(std::cin>>temp){
		if(temp == "done") return;
		name.push_back(temp);
	}
	std::cin.clear();
}

void Name_pairs::read_ages(){
	double temp;
	std::cout << "Enter space separated ages type 'done' when finished:\n";
	while(std::cin>>temp){
		age.push_back(temp);
	}
	std::cin.clear();
}

void Name_pairs::print(){
	if(name.size() != age.size()){
		error("print() name and age must have the same number of elements");
	}
	for(int i=0;i<name.size();i++){
		cout << name[i] << ' ' << age[i] << '\n';
	}
}

void Name_pairs::sort(){
	if(name.size() != age.size()){
		error("sort() name and age must have the same number of elements");
	}
	vector<string> old_name = name;
	vector<double> old_age = age;
	
	std::sort(name.begin(), name.end());
	for(int i=0; i<name.size(); i++){
		for(int j=0; j<old_name.size(); j++){
			if(name[i] == old_name[j]){
				age[i] = old_age[j];
				break;
			}
		}
	}
}