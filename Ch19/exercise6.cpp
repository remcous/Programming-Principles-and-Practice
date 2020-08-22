/*
    exercise6.cpp

    Revision History:
*/

#include <iostream>
#include <vector>
#include <cmath>
#include <type_traits>

using namespace std;

/****************************************
*           CLASS DEFINITIONS
****************************************/

template<typename T> class Number{
public:
	// CONSTRUCTOR
	Number():num{0}{}			// default constructor
	explicit Number(T val): num{val}{}	// assigned constructor

	// COPY
	Number(const Number<T>& a)	// copy constructor
		:num{a.num}{}
	Number<T>& operator=(const Number<T>& a){num = a.num;}

	// MOVE
	Number(Number<T>&& a)		// move constructor
		:num{a.num}{}
	Number<T>& operator=(Number<T>&& a){num = a.num;}

	// MATH OPERATORS
	T& operator=(const T& a){num = a;}
	Number<T> operator+(const Number<T>& b) const;
	Number<T> operator-(const Number<T>& b) const;
	Number<T> operator*(const Number<T>& b) const;
	Number<T> operator/(const Number<T>& b) const;
	Number<T> operator%(const Number<T>& b) const;

	// CAST
	operator T() const{return num;}

	// FRIEND I/O
	template<typename U> friend ostream& operator<<(ostream&, const Number<U>&);
	template<typename U> friend istream& operator>>(istream&, Number<U>&);
private:
	T num;	
};

/****************************************
*           FUNCTION PROTOTYPES
****************************************/

template<typename T> ostream& operator<<(ostream&, const Number<T>&);
template<typename T> istream& operator>>(istream&, Number<T>&);

template<typename T, typename U> 
typename std::common_type<T,U>::type 
f(const std::vector<T>& vt, const std::vector<U>& vu);

/****************************************
*           GLOBAL VARIABLES
****************************************/

/****************************************
*             MAIN FUNCTION
****************************************/

int main(){
    try{
    	// default construction
        vector<Number<int>> vni(1);
        // default construction
        vector<Number<double>> vnd(1);

        // initialized construction
        for(int i=1; i<=5; i++)
        {
        	Number<int> temp_i{i};
        	Number<double> temp_d{1.1*i};
        	vni.push_back(temp_i);
        	vnd.push_back(temp_d);
        }

    	// Copy construction
    	vni.push_back(vni[0]);
    	vnd.push_back(vnd[0]);

    	{
    		Number<int> temp_i;
        	Number<double> temp_d;

    		// Test input
    	    cout << "Enter an int: ";
    	    cin >> temp_i;
    	    vni.push_back(temp_i);

    	    cout << "Enter a double: ";
    	    cin >> temp_d;
    	    vnd.push_back(temp_d);
    	}

    	cout << '\n';	// visual separation

    	// Output all values
    	for(int i=0; i<vni.size(); i++)
    	{
    		cout << "vni[" << i << "]: " << vni[i] << endl;
    	}

    	cout << '\n';	// visual separation

    	for(int i=0; i<vnd.size(); i++)
    	{
    		cout << "vnd[" << i << "]: " << vnd[i] << endl;
    	}

    	cout << '\n';	// visual separation

    	// Test math operations
    	cout << "vni[3] + vni[2] = " << vni[3] + vni[2] << endl;
    	cout << "vni[3] - vni[2] = " << vni[3] - vni[2] << endl;
    	cout << "vni[3] * vni[2] = " << vni[3] * vni[2] << endl;
    	cout << "vni[3] / vni[2] = " << vni[3] / vni[2] << endl;
    	cout << "vni[3] % vni[2] = " << vni[3] % vni[2] << endl;

    	cout << '\n';	// visual separation

    	cout << "vnd[3] + vnd[2] = " << vnd[3] + vnd[2] << endl;
    	cout << "vnd[3] - vnd[2] = " << vnd[3] - vnd[2] << endl;
    	cout << "vnd[3] * vnd[2] = " << vnd[3] * vnd[2] << endl;
    	cout << "vnd[3] / vnd[2] = " << vnd[3] / vnd[2] << endl;
    	cout << "vnd[3] % vnd[2] = " << vnd[3] % vnd[2] << endl;

    	cout << "\nExercise7:\n";

    	cout << "f(vni, vnd) = " << f(vni, vnd) << endl;

    	cout << "f(vnd, vni) = " << f(vnd, vni) << endl;
    }
    catch(exception& e){
        cerr << e.what() << '\n';
        return 1;
    }
    catch(...){
        cerr << "exception\n";
        return 2;
    }
    return 0;
}

/****************************************
*       FUNCTION DEFINITIONS - NUMBER
****************************************/

template<typename T>
Number<T> Number<T>::operator+(const Number<T>& b) const
{
	Number<T> temp{num + b.num};
	return temp;
}

template<typename T>
Number<T> Number<T>::operator-(const Number<T>& b) const
{
	Number<T> temp{num - b.num};
	return temp;
}

template<typename T>
Number<T> Number<T>::operator*(const Number<T>& b) const
{
	Number<T> temp{num * b.num};
	return temp;
}

template<typename T>
Number<T> Number<T>::operator/(const Number<T>& b) const
{
	Number<T> temp{num / b.num};
	return temp;
}

template<typename T>
Number<T> Number<T>::operator%(const Number<T>& b) const
{
	Number<T> temp{fmod(num, b.num)};
	return temp;
}

template<typename T>
ostream& operator<<(ostream& os, const Number<T>& a)
{
	os << a.num;
}

template<typename T>
istream& operator>>(istream& is, Number<T>& a)
{
	is >> a.num;
}

template<typename T, typename U> 
typename std::common_type<T,U>::type 
f(const std::vector<T>& vt, const std::vector<U>& vu)
{
	typename std::common_type<T,U>::type sum = 0;
	int min_size = std::min(vt.size(), vu.size());

	for(int i=0; i<min_size; i++)
	{
		sum += vt[i] * vu[i];
	}
	return sum;
}
