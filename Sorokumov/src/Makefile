all: prog

prog: source.o binSTree.o 
	g++ source.o binSTree.o -o program

source.o: source.cpp
	g++ -c source.cpp

binSTree.o: binSTree.cpp
	g++ -c binSTree.cpp
	
clean:
	rm -rf *.o 
	rm program
