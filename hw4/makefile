all: hw4

hw4: main.cpp sign_record.o date.o
	g++ main.cpp sign_record.o date.o -o hw4

sign_record.o: sign_record.cpp
	g++ -c sign_record.cpp

date.o: date.cpp
	g++ -c date.cpp

clean:
	rm *.o hw4
