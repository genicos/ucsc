CFLAGS = -Werror -Wall -Wextra -Wpedantic 
CC = clang

.PHONY: all clean valgrind testval

all: 
	make encode
	make decode

encode: encode.o word.o trie.o io.o
	$(CC) encode.o word.o trie.o io.o -o encode

encode.o: encode.c
	$(CC) $(CFLAGS) -c encode.c

decode: decode.o word.o trie.o io.o 
	$(CC) decode.o word.o trie.o io.o -o decode

decode.o: decode.c
	$(CC) $(CFLAGS) -c decode.c

testval: 
	make clean
	make test
	valgrind --leak-check=yes ./test

test: test.o word.o trie.o io.o
	$(CC) test.o word.o trie.o io.o -o test

test.o: test.c
	$(CC) $(CFLAGS) -c test.c

word.o: word.c
	$(CC) $(CFLAGS) -c word.c

trie.o: trie.c
	$(CC) $(CFLAGS) -c trie.c

io.o: io.c
	$(CC) $(CFLAGS) -c io.c 

valgrind:
	make clean
	make all
	valgrind --leak-check=yes ./encode -i bible.txt -o compressed -v
	valgrind --leak-check=yes ./decode -i compressed -o val-bible-out -v

infer: 
	make clean
	infer-capture -- make all
	infer-analyze -- make all

clean: 
	rm -f test.o word.o trie.o io.o decode.o encode.o encode decode compressed val-bible-out
	rm -f test header1 header2 header3 header4 pairsout wordsout -r infer-out 
