all: calculator exercise1 exercise2 exercise3 exercise4

.cpp:
	g++ -std=c++14 $< -o $(<:.cpp=.exe)

clean:
	rm *.exe