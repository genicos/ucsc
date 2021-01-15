CFLAGS = -Wpedantic -Werror -Wall -Wextra
CC = clang $(CFLAGS)

sorting: sorting.o bubble.o shell.o quick.o binary.o merge.o
	$(CC) sorting.o bubble.o shell.o quick.o binary.o merge.o -o sorting

sorting.o: sorting.c
	$(CC) -c sorting.c

bubble.o: bubble.c bubble.h
	$(CC) -c bubble.c

shell.o: shell.c shell.h
	$(CC) -c shell.c

quick.o: quick.c quick.h
	$(CC) -c quick.c

binary.o: binary.c binary.h
	$(CC) -c binary.c

merge.o: merge.c merge.h
	$(CC) -c merge.c

clean:
	rm -f sorting sorting.o bubble.o shell.o quick.o binary.o merge.o -r infer-out

infer:
	make clean
	infer-capture -- make
	infer-analyze -- make

valgrind:
	make
	valgrind --leak-check=yes sorting -A
