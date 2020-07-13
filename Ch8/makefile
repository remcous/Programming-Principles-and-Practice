all: use

use: my.o use.o
	g++ -std=c++14 -o use.exe use.o my.o

use.o: use.cpp my.h
	g++ -std=c++14 -c use.cpp

my.o: my.cpp my.h
	g++ -std=c++14 -c my.cpp

clean:
	rm *.exe
	rm *.o