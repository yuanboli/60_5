blood.out: blood.o bloodRunner.o list.o
	g++ -Wall -ansi -g -o blood.out blood.o bloodRunner.o list.o 

blood.o: blood.cpp bloodShort.h bloodRunner.h 
	g++ -Wall -ansi -g -c blood.cpp

bloodRunner.o: bloodRunner.cpp bloodRunner.h CPUTimer.h blood.h  
	g++ -Wall -ansi -g -c bloodRunner.cpp

list.o: list.h list.cpp
	g++ -Wall -ansi -g -c list.cpp

clean:
	rm -f blood.out blood.o bloodRunner.o list.o

'test:
	
