all:hello

hello: main.o Reading.o Tree.o
	g++ main.o Reading.o Tree.o -o hello.exe

main.o: main.cpp
	g++ -c main.cpp

Reading.o: Reading.cpp Reading.h
	g++ -c Reading.cpp

Tree.o: Tree.cpp Tree.h
	g++ -c Tree.cpp

clean:
	rm *.o hello

	
