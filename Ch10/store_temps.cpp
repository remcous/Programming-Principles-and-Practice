#include "../std_lib_facilities.h"

struct Reading{			// a temperature reading
	int hour{0};			// hour after midnight [0:23]
	double temperature{0};	// in fahrenheit
};

ostream& operator<<(ostream& os, const Reading& reading);
istream& operator>>(istream& is, Reading& reading);

#define OUT_FILE "raw_temps.txt"
#define NUM_READINGS 50

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
			temp = ((double)rand()/RAND_MAX)*(108)-4;
			
			reading.hour = hr;
			reading.temperature = temp;

			ofs << reading << '\n';
		}
	}catch(exception& e){
		cerr << e.what() << '\n';
		return 1;
	}
	return 0;
}

ostream& operator<<(ostream& os, const Reading& reading){
	os << reading.hour << " : " << reading.temperature;
	return os;
}

istream& operator>>(istream& is, Reading& reading){
	int hr;
	double temp;
	is >> hr >> temp;
	if(hr<0 || hr > 23) error(">> Reading failed - hour out of bounds");
	if(temp < -459.67) error("Temperature is below absolute zero...are you sure?");
	reading.hour = hr; reading.temperature = temp;
	return is;
}