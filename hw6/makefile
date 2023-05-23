all: hw6

hw6: main.cpp trie.o database.o
	g++ main.cpp trie.o database.o -o hw6

database.o: database.cpp
	g++ -c database.cpp

trie.o: trie.cpp
	g++ -c trie.cpp

clean:
	rm *.o hw6
