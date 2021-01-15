CXX = gcc
CXXFLAGS = -Wall
    
twain: twain.o ll.o
	$(CXX) -g $(CXXFLAGS) twain.o ll.o -o twain

twain.o: twain.c
	$(CXX) -g $(CXXFLAGS) -c twain.c


test-ll: test-ll.o ll.o
	$(CXX) -g $(CXXFLAGS) test-ll.o ll.o -o test-ll

test-ll.o: test-ll.c
	$(CXX) -g $(CXXFLAGS) -c test-ll.c

ll.o: ll.c
	$(CXX) -g $(CXXFLAGS) -c ll.c

reset_examples:
	cp Tests/simple-input.txt simple-input.txt
	cp Tests/simple-output.txt simple-output.txt
	
valtest-ll:
	make clean
	make test-ll
	valgrind --leak-check=yes ./test-ll

valtwain:	
	make clean
	make twain
	valgrind --leak-check=yes ./twain simple-input.txt OUT

clean:
	rm -f *.o 
	rm -f twain OUT
	rm -f test-ll
