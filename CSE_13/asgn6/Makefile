CFLAGS = -Wpedantic -Wall -Werror -Wextra -std=c99
CC = clang

.PHONY: all
all:
	make newspeak

newspeak: newspeak.o bf.o hash.o ll.o bv.o gs.o parser.o speck.o
	$(CC) newspeak.o bf.o hash.o ll.o bv.o gs.o parser.o speck.o -o newspeak

newspeak.o: newspeak.c
	$(CC) $(CFLAGS) -c newspeak.c

bf.o: bf.c bv.c
	$(CC) $(CFLAGS) -c bf.c

hash.o: hash.c ll.c gs.c
	$(CC) $(CFLAGS) -c hash.c

ll.o: ll.c gs.c
	$(CC) $(CFLAGS) -c ll.c

bv.o: bv.c
	$(CC) $(CFLAGS) -c bv.c

gs.o: gs.c
	$(CC) $(CFLAGS) -c gs.c

parser.o: parser.c
	$(CC) $(CFLAGS) -c parser.c

speck.o: speck.c
	$(CC) $(CFLAGS) -c speck.c

.PHONY: clean
clean: 
	rm -f newspeak newspeak.o bf.o hash.o ll.o gs.o parser.o speck.o -r infer-out

.PHONY: infer
infer:
	make clean
	infer-capture -- make
	infer-analyze -- make

.PHONY: valgrind
valgrind:
	make newspeak
	valgrind --leak-check=yes ./newspeak
