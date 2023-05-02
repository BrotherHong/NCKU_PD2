all: hw5

hw5: main.cpp trie.o
	g++ main.cpp trie.o -o hw5

trie.o: trie.cpp
	g++ -c trie.cpp

clean:
	rm *.o hw5
