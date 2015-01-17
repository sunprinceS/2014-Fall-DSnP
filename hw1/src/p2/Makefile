all:p2a.cpp p2b.cpp
	g++ -o progA p2a.cpp
	g++ -o progB p2b.cpp
	g++ -o progC p2c.cpp
runall:progA progB
	./progA
	./progB
	./progC
p2a:p2a.cpp
	g++ -o progA p2a.cpp
	./progA
p2b:p2b.cpp
	g++ -o progB p2b.cpp
	./progB
p2c:p2c.cpp
	g++ -o progC p2c.cpp
	./progC
clear:
	rm -i  progA
	rm -i  progB
	rm -i  progC
