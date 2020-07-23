#ifndef READING_H
#define READING_H

double celcius_to_freedom(double temp);

struct Reading{			// a temperature reading
	int hour;			// hour after midnight [0:23]
	double temperature;	// in fahrenheit
	Reading():hour{0}, temperature{0}{};
	Reading(int hr, double temp):
		hour{hr}, temperature{temp}{}
};

ostream& operator<<(ostream& os, const Reading& reading){
	os << reading.hour << " " << reading.temperature;
	return os;
}

istream& operator>>(istream& is, Reading& reading){
	int hr;
	double temp;
	char unit;
	is >> hr >> temp >> unit;
	if(is.bad()) error("Oops: Reading istream failed\n");
	if(is.eof() || is.fail()) return is;
	if(hr<0 || hr > 23) error(">> Reading failed - hour out of bounds ", hr);
	if(temp < -459.67) error("Temperature is below absolute zero...are you sure? ", temp);
	if(unit == 'c') temp = celcius_to_freedom(temp);
	else if(unit != 'f') error ("Unknown temperature unit ", unit);
	Reading r{hr,temp};
	reading = r;
	return is;
}

bool operator<(const Reading& a, const Reading& b){
	if(a.temperature < b.temperature) return true;
	return false;
}

bool operator>(const Reading& a, const Reading& b){
	if(a.temperature > b.temperature) return true;
	return false;
}

bool operator==(const Reading& a, const Reading& b){
	if(a.temperature == b.temperature) return true;
	return false;
}

bool operator!=(const Reading& a, const Reading& b){
	if(a.temperature != b.temperature) return true;
	return false;
}

double celcius_to_freedom(double temp){
	return (temp * 9.0/5.0) + 32;
}

#endif	// READING_H