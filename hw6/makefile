all: map

hw6: main.cpp trie.o database.o
	g++ main.cpp trie.o database.o -o hw6

map: main.cpp database_map.o trie.o
	g++ main.cpp database_map.o trie.o -o hw6

database.o: database.cpp
	g++ -c database.cpp

database_map.o: database_map.cpp
	g++ -c database_map.cpp

trie.o: trie.cpp
	g++ -c trie.cpp

clean:
	rm *.o hw6
