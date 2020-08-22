/*
    exercise12.cpp

    Revision History:
*/

#include <iostream>
#include <fstream>

using namespace std;

/****************************************
*           CLASS DEFINITIONS
****************************************/

class file_not_found{
public:
	file_not_found():fname{""}{}
	file_not_found(const string& s):fname{s}{}
	string fname;
};

class File_handle{
public:
	File_handle(const string& s)
		:ifs{s}
		{
			if(!ifs) throw file_not_found{s};
		}
	~File_handle(){ifs.close();}

	template<typename T> ifstream& operator>>(T& t){
		ifs >> t;
		return ifs;
	}

	operator bool() const
	{
		return !ifs.eof();
	}
private:
	File_handle() = delete;
	ifstream ifs;
};

/****************************************
*           FUNCTION PROTOTYPES
****************************************/

/****************************************
*           GLOBAL VARIABLES
****************************************/

/****************************************
*             MAIN FUNCTION
****************************************/

int main(){
    try{
        File_handle fh{"exercise12.cpp"};

        char s[50];
        while(fh)
        {
	        fh >> s;
	
	        cout << s;
       	}
    }
    catch(exception& e){
        cerr << e.what() << '\n';
        return 1;
    }
    catch(file_not_found& f){
    	cerr << "Error: File \"" << f.fname << "\" was not found!\n";
    	return 3;
    }
    catch(...){
        cerr << "exception\n";
        return 2;
    }
    return 0;
}

/****************************************
*   FUNCTION DEFINITIONS - File_handle
****************************************/
