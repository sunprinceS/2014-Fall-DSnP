p1a:p1a.o p1a.main.cpp
	g++ -o p1a p1a.main.cpp p1a.o 
	./p1a > p1a.out
p1a.o:p1a.cpp p1a.h
	g++ -c p1a.cpp
p1b:p1b.o p1b.main.cpp
	g++ -o p1b p1b.main.cpp p1b.o
	./p1b > p1b.out
p1b.o:p1b.cpp p1a.h
	g++ -c p1b.cpp
bug:p1.bug.cpp p1a.o
	g++ -g -o  p1.bug p1.bug.cpp p1a.o
clear:
	rm -f *.o 
	rm -f *.log
	rm -f *~
