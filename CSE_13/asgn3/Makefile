CFLAGS = -Wall -Wextra -Werror -Wpedantic
CC = clang $(CFLAGS)

pathfinder: pathfinder.o stack.o 
	$(CC) -o pathfinder pathfinder.o stack.o 

pathfinder.o: pathfinder.c
	$(CC) -c pathfinder.c

stack.o: stack.c
	$(CC) -c stack.c

clean:
	rm -f pathfinder pathfinder.o stack.o infer-out
infer:
	make clean; infer-capture -- make; infer-analyze -- make

