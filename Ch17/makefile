all: libraries Lines_window GUI_Drill

.cpp:
	g++ -w -Wall -Wno-cpp -std=c++14 ../Libraries/Graph.o ../Libraries/Window.o ../Libraries/GUI.o ../Libraries/Simple_window.o $< `fltk-config --ldflags --use-images` -o $(<:.cpp=.exe)

libraries: ../Libraries/Graph.cpp ../Libraries/Window.cpp ../Libraries/GUI.cpp ../Libraries/Simple_window.cpp
	g++ -std=c++14 -c ../Libraries/Graph.cpp -o ../Libraries/Graph.o
	g++ -std=c++14 -c ../Libraries/Window.cpp -o ../Libraries/Window.o
	g++ -std=c++14 -c ../Libraries/GUI.cpp -o ../Libraries/GUI.o
	g++ -std=c++14 -c ../Libraries/Simple_window.cpp -o ../Libraries/Simple_window.o

clean:
	rm *.exe