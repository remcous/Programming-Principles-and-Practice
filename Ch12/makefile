all: 

.cpp:
	g++ -w -Wall -Wno-cpp -std=c++11 Graph.cpp Window.cpp GUI.cpp Simple_window.cpp $< `fltk-config --ldflags --use-images` -o $(<:.cpp=.exe)
clean:
	rm *.exe