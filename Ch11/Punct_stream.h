#ifndef PUNCT_STREAM_H
#define PUNCT_STREAM_H
#include <string>

class Punct_stream{	// like an istream, but the user can add to
					// the set of whitespace characters
public:
	Punct_stream(istream& is)
		: source{is}, sensitive{true}{}

	void whitespace(const string& s)	// make s the whitespace set
		{white = s;}
	void add_white(char c){white += c;}	// add to the whitespace set
	bool is_whitespace(char c);			// is c in the whitespace set?
	void case_sensitive(bool b){sensitive = b;}
	bool is_case_sensitive(){return sensitive;}

	Punct_stream& operator>>(string& s);
	operator bool();
private:
	istream& source;		// character source
	istringstream buffer;	// we let buffer do our formatting
	string white;			// characters considered "whitespace"
	bool sensitive;			// is the stream case-sensitive?
};

Punct_stream& Punct_stream::operator>>(string& s){
	while(!(buffer>>s)){	// try to read from buffer
		if(buffer.bad() || !source.good()) return *this;
		buffer.clear();

		string line;
		getline(source, line);	// get a line from source

		// do character replacement as needed:
		for(char& ch : line)
			if(is_whitespace(ch))
				ch = ' ';			// to space
			else if(!sensitive)
				ch = tolower(ch);	// to lower case

		buffer.str(line);		// put string into stream
	}
	return *this;
}

bool Punct_stream::is_whitespace(char c){
	for(char w : white)
		if(c==w) return true;
	return false;
}

Punct_stream::operator bool(){
	return !(source.fail() || source.bad()) && buffer.good();
}

#endif	// PUNCT_STREAM_H