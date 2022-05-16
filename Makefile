
output: main.o editor.o buffer.o
	g++ main.o editor.o buffer.o -o femto -lncurses

main.o: main.cpp
	g++ -c main.cpp
editor.o: editor.cpp editor.h
	g++ -c editor.cpp
buffer.o: buffer.cpp
	g++ -c buffer.cpp

clean:
	rm *.o
