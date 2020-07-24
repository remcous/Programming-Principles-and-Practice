all: binary_int

.cpp:
	g++ -std=c++14 $< -o $(<:.cpp=.exe)

clean:
	rm *.exe