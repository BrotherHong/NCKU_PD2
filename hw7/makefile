all: hw7

hw7: main.cpp trie.o database.o
	g++ main.cpp trie.o database.o -o hw7

map: main.cpp database_map.o trie.o
	g++ main.cpp database_map.o trie.o -o hw7

database.o: database.cpp
	g++ -c database.cpp

database_map.o: database_map.cpp
	g++ -c database_map.cpp

trie.o: trie.cpp
	g++ -c trie.cpp

clean:
	rm *.o hw7
