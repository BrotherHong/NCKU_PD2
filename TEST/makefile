
all: test

test: test.cpp tool.o
	g++ test.cpp tool.o -o test

tool.o: tool.cpp
	g++ -c tool.cpp

clean: 
	rm *.o test
