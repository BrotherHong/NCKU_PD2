all: hw5

hw5: main.cpp trie.o database.o
	g++ main.cpp trie.o database.o -o hw5

database.o: database.cpp
	g++ -c database.cpp

trie.o: trie.cpp
	g++ -c trie.cpp

clean:
	rm *.o hw5
