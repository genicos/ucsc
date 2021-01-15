CFLAGS = -Wall -Wextra -Werror -Wpedantic
CC = clang $(CFLAGS)

sequence: sequence.o sieve.o bv.o
	$(CC) sequence.o sieve.o bv.o -o sequence -lm

sequence.o: sequence.c sieve.h bv.h
	$(CC) -c sequence.c

sieve.o: sieve.c sieve.h bv.h
	$(CC) -c sieve.c 

bv.o: bv.c bv.h
	$(CC) -c bv.c

clean:
	rm -f sequence sequence.o sieve.o bv.o -r infer-out

infer:
	make clean
	infer-capture -- make
	infer-analyze -- make
