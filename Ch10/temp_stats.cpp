#include "../std_lib_facilities.h"
#include "reading.h"

#define IN_FILE "raw_temps.txt"

int main(){
	try{
		ifstream ifs{IN_FILE};
		if(!ifs) error("Couldn't open input file: ", IN_FILE);

		vector<Reading> readings;

		for(Reading r; ifs>>r;)
			readings.push_back(r);

		// Calculate the mean of the data set
		double mean = 0;

		for(Reading r: readings){
			mean += r.temperature;
		}
		mean /= readings.size();

		cout << "The mean of the data is: " << mean << '\n';

		// Calculate the median of the data set
		sort(readings.begin(), readings.end());
		double median;
		if(readings.size() == 1) median = readings[0].temperature;
		else if(readings.size()%2 == 0){
			median = (readings[readings.size()/2].temperature 
				+ readings[readings.size()/2-1].temperature)/2;
		}else{
			median = readings[readings.size()/2].temperature;
		}

		cout << "The median of the data is: " << median << '\n';
	}catch(exception& e){
		cerr << e.what() << '\n';
		return 1;
	}catch(...){
		cerr << "Unknown exception\n";
		return 2;
	}

	return 0;
}