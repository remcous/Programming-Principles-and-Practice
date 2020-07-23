#include "../std_lib_facilities.h"
#include "reading.h"

#define OUT_FILE "raw_temps.txt"
#define NUM_READINGS 50
#define MIN_TEMP -4
#define MAX_TEMP 104

int main(){
	try{
		ofstream ofs{OUT_FILE};
		if(!ofs) error("Can't open file ", OUT_FILE);
		
		srand(time(0));
		
		for(int i=0; i<NUM_READINGS; i++){
			static int hr;
			static double temp;
			static Reading reading;

			hr = rand() % 24;
			// mapping random doubles to range -4:104 F (-20:40 C)
			temp = ((double)rand()/RAND_MAX)
				* (MAX_TEMP-MIN_TEMP)+MIN_TEMP;

			reading.hour = hr;
			reading.temperature = temp;

			ofs << reading;

			if(rand()%2 == 0) ofs << "f\n";
			else ofs << "c\n";

		}
	}catch(exception& e){
		cerr << e.what() << '\n';
		return 1;
	}
	return 0;
}