/*
    binary_search.cpp

    Revision History:
*/

#include <iostream>
#include <vector>
#include <string>
#include <cctype>
#include <fstream>
#include <sstream>

using namespace std;

/****************************************
*           CLASS DEFINITIONS
****************************************/

struct Test{
public:
	string label;
	int val;
	vector<int> seq;
	bool res;
};

struct Test_read_error{
	Test_read_error(){}
};

/****************************************
*           FUNCTION PROTOTYPES
****************************************/

template <typename Iter, typename Value> bool binary_search(Iter start, Iter end, Value val);
istream& operator>>(istream& is, Test& t);

int test_all(istream& is);

/****************************************
*           GLOBAL VARIABLES
****************************************/

/****************************************
*             MAIN FUNCTION
****************************************/

int main(){
	/*
	vector<int> v { 1,2,3,5,8,13,21 };

	if (binary_search(v.begin(),v.end(), 1) == false) cout << "failed"; 
	if (binary_search(v.begin(),v.end(), 5) == false) cout << "failed"; 
	if (binary_search(v.begin(),v.end(), 8) == false) cout << "failed"; 
	if (binary_search(v.begin(),v.end(), 21) == false) cout << "failed"; 
	if (binary_search(v.begin(),v.end(), -7) == true) cout << "failed"; 
	if (binary_search(v.begin(),v.end(), 4) == true) cout << "failed"; 
	if (binary_search(v.begin(),v.end(), 22) == true) cout << "failed";

	*/

	/*
	vector<int> v { 1,2,3,5,8,13,21 };
	for (int x : {1,5,8,21,-7,2,44})
		if (binary_search(v.begin(),v.end(),x) == false) cout << x << " failed\n";
	*/

	try{
		ifstream ifs{"my_tests.txt"};
		if(!ifs.is_open()) throw 1;

		int errors = test_all(ifs);
		cout << "number of errors: " << errors << endl;
	}
	catch(Test_read_error)
	{
		cerr << "Test_read_error encounted!\n";
	}
	catch(...)
	{
		cerr << "Exception encountered\n";
	}

    return 0;
}

/****************************************
*       FUNCTION DEFINITIONS - GLOBAL
****************************************/

template <typename Iter, typename Value> 
bool binary_search(Iter start, Iter end, Value val)
{
	int count = 0;

	for(count = 0; start+count != end; count++);

	if(count == 0) return false;

	int left_end = 0;
	int right_end = count;
	int check_point = (right_end + left_end) / 2;

	while(check_point >= left_end && check_point <= right_end)
	{
		static Value current, previous = *start;
		current = *(start + check_point);

		if(current == val)
		{
			return true;
		}
		else if(current > val)
		{
			right_end = check_point;
		}
		else
		{
			left_end = check_point;
		}

		if(previous == current) break;
		if(left_end == right_end) break;

		previous = current;
		check_point = (right_end + left_end) / 2;
	}

	return false;
}

istream& operator>>(istream& is, Test& t)
{
	is.clear();

	string test_values;

	while(getline(is, test_values))
	{
		if(!test_values.empty())
			break;
	}

	istringstream iss{test_values};

	char a,b,c,temp;
	int num;

	if(iss >> a >> t.label >> t.val >> b && (a != '{' && b != '{'))
	{
		throw Test_read_error();
	}

	t.seq.clear();

	while(true){
		iss.get(temp);
	
		if(isspace(temp)) continue;

		if(isdigit(temp))
		{	
			iss.putback(temp);
			iss >> num;
			t.seq.push_back(num);
		}
		else if(temp == '-')
		{
			iss >> num;
			t.seq.push_back(-1*num);
		}
		else if(temp == '}')
		{
			break;
		}
		else throw Test_read_error();
	}

	if(iss >> t.res >> c && c != '}') throw Test_read_error();

	is.get(temp);

	if(!is.eof()) is.putback(temp);

	return is;
}

int test_all(istream& is) {
	int error_count = 0; 
	for (Test t; is>>t; ) {
		bool r = binary_search(t.seq.begin(), t.seq.end(), t.val); 

		if (r !=t.res) {
			cout << "failure: test " << t.label << " binary_search: "
				<< t.seq.size() << " elements, val==" << t.val
				<< " –> " << t.res << '\n'; 
			++error_count;
		}
	}
	return error_count; 
}
