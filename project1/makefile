CC=g++
DebugFlag=-g

p1: main.o term.o
	$(CC) $(DebugFlag) -o p1 main.o term.o

term.o: term.h term.cpp
	$(CC) $(DebugFlag) -c term.cpp

main.o: term.h main.cpp
	$(CC) $(DebugFlag) -c main.cpp

clean:
	rm -rf *.o p1
