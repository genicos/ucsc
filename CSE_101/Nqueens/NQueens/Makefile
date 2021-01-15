CXX = g++
CXXFLAGS = -Wall -std=c++11

nqueens: nqueens.o chess.o
	$(CXX) -g $(CXXFLAGS) -o $@ $^

nqueens.o: nqueens.cpp
	$(CXX) -g $(CXXFLAGS) -c nqueens.cpp


tester: tester.o chess.o
	$(CXX) -g $(CXXFLAGS) -o $@ $^

tester.o: tester.cpp
	$(CXX) -g $(CXXFLAGS) -c $^


chess.o: chess.cpp chess.h
	$(CXX) -g $(CXXFLAGS) -c chess.cpp
clean:
	rm -f *.o
	rm -f nqueens
	rm -f tester
