femto: main.o editor.o buffer.o prompt.o
	g++ obj/main.o obj/editor.o obj/buffer.o obj/prompt.o -o femto -lncurses
main.o: src/main.cpp
	g++ -c -Wall -O2 src/main.cpp -o obj/main.o
editor.o: src/editor.cpp lib/editor.h
	g++ -c -Wall -O2 src/editor.cpp -o obj/editor.o
buffer.o: src/buffer.cpp lib/buffer.h
	g++ -c -Wall -O2 src/buffer.cpp -o obj/buffer.o
prompt.o: src/prompt.cpp lib/prompt.h
	g++ -c -Wall -O2 src/prompt.cpp -o obj/prompt.o
clean:
	rm obj/*.o femto untitled*
