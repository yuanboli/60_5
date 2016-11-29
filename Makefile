blood.out: blood.o bloodRunner.o list.o BinaryHeap.o BinaryMaxHeap.o
	g++ -Wall -ansi -g -o blood.out blood.o bloodRunner.o list.o BinaryHeap.o BinaryMaxHeap.o

blood.o: blood.cpp bloodShort.h bloodRunner.h 
	g++ -Wall -ansi -g -c blood.cpp

bloodRunner.o: bloodRunner.cpp bloodRunner.h CPUTimer.h blood.h  
	g++ -Wall -ansi -g -c bloodRunner.cpp

list.o: list.h list.cpp
	g++ -Wall -ansi -g -c list.cpp

BinaryHeap.o: BinaryHeap.h BinaryHeap.cpp
	g++ -Wall -ansi -g -c BinaryHeap.cpp

BinaryMaxHeap.o:	BinaryMaxHeap.h BinaryMaxHeap.cpp
	g++ -Wall -ansi -g -c BinaryMaxHeap.cpp

clean:
	rm -f blood.out *.o

test: 
	g++ test.cpp -g -c
	g++ -o test.out -g test.o list.o
	
