all: hw3

hw3: main.cpp check_record.o mytime.o
	g++ main.cpp check_record.o mytime.o -o hw3

check_record.o: check_record.cpp
	g++ -c check_record.cpp

mytime.o: mytime.cpp
	g++ -c mytime.cpp

clean:
	rm *.o hw3
