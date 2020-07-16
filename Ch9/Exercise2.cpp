/******************************************************
*	Exercise 2: design and implement a name_pair class
*	By: Remi Coussement
*	Rev:
*		Exercise 3 - add support for <<, ==, and !=
*				July 2020
*		Exercise 2 - Name_pairs and member functions 
*				July 2020		
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
	const vector<string>& get_name() const{return name;}
	const vector<double>& get_age() const{return age;}
	Name_pairs(){}
private:
	vector<string> name;
	vector<double> age;
};

/**********************************
*		  FUNCTION PROTOTYPE
**********************************/

ostream& operator<<(ostream& os, const Name_pairs& np);
bool operator==(const Name_pairs& lnp, const Name_pairs& rnp);
bool operator!=(const Name_pairs& lnp, const Name_pairs& rnp);

/**********************************
*			MAIN PROGRAM
**********************************/

int main(){
	try{
		Name_pairs np;

		np.read_names();
		np.read_ages();

		cout << "First order:\n" << np;

		np.sort();
		cout << "\n\nSorted order:\n" << np;

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

/**********************************
*		   GLOBAL FUNCTIONS
**********************************/

ostream& operator<<(ostream& os, const Name_pairs& np){
	vector<string> name = np.get_name();
	vector<double> age = np.get_age();
	if(name.size() != age.size()){
		error("print() name and age must have the same number of elements");
	}
	for(int i=0;i<name.size();i++){
		os << name[i] << ' ' << age[i] << '\n';
	}
	return os;
}

bool operator==(const Name_pairs& lnp, const Name_pairs& rnp){
	if(lnp.get_name().size() != rnp.get_name().size() ||
		lnp.get_name().size() != lnp.get_age().size() ||
		lnp.get_name().size() != rnp.get_age().size())
		return false;
	vector<string> left_name = lnp.get_name();
	vector<string> right_name = rnp.get_name();
	vector<double> left_age = lnp.get_age();
	vector<double> right_age = rnp.get_age();
	for(int i=0;i<left_name.size();i++){
		if(left_name[i] != right_name[i]) return false;
		if(left_age[i] != right_age[i]) return false;
	}
	return true;
}

bool operator!=(const Name_pairs& lnp, const Name_pairs& rnp){
	if(lnp.get_name().size() != rnp.get_name().size() ||
		lnp.get_name().size() != lnp.get_age().size() ||
		lnp.get_name().size() != rnp.get_age().size())
		return true;
	vector<string> left_name = lnp.get_name();
	vector<string> right_name = rnp.get_name();
	vector<double> left_age = lnp.get_age();
	vector<double> right_age = rnp.get_age();
	for(int i=0;i<left_name.size();i++){
		if(left_name[i] != right_name[i]) return true;
		if(left_age[i] != right_age[i]) return true;
	}
	return false;
}