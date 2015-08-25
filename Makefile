all: MyExceptions.h Driver.o Utility.o Graph.o
	g++ -ansi -Wall MyExceptions.h Driver.o Utility.o Graph.o -o Driver.out

Graph.o: Graph.cpp
	g++ -ansi -Wall -c Graph.cpp

Utility.o: Utility.cpp
	g++ -ansi -Wall -c Utility.cpp

Driver.o: Driver.cpp
	g++ -ansi -Wall -c Driver.cpp

run:
	./Driver.out $(FILE)

clean:
	rm -rf *.o
	rm -f *.out
	rm -f *~*.h.gch *#[
