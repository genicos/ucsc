CXX = g++
CXXFLAGS = -Wall -std=c++11

wordrange: wordrange.o bst.o
	$(CXX) -g $(CXXFLAGS) -o $@ $^

wordrange.o: wordrange.cpp
	$(CXX) -g $(CXXFLAGS) -c $^


bst.o: bst.cpp bst.h
	$(CXX) -g $(CXXFLAGS) -c $^

clean: 
	rm -f *.o
	rm -f wordrange
	rm -f bst.h.gch