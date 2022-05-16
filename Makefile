
output: main.o editor.o buffer.o
	g++ obj/main.o obj/editor.o obj/buffer.o -o femto -lncurses

main.o: src/main.cpp lib/editor.h
	g++ -c src/main.cpp -o obj/main.o
editor.o: src/editor.cpp lib/editor.h
	g++ -c src/editor.cpp -o obj/editor.o
buffer.o: src/buffer.cpp lib/buffer.h
	g++ -c src/buffer.cpp -o obj/buffer.o

clean:
	rm obj/*.o
