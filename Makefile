CXX      = /usr/sup/bin/clang++
CXXFLAGS = --std=c++11 -Wshadow -Wall -Wextra -g3

%.o: %.cpp $(shell echo *.h)
	$(CXX) $(CXXFLAGS) -c $<

findpath: findpath.o Location.o Graph.o
	$(CXX) -o $@ $^

test: testGraph.o Location.o Graph.o
	$(CXX) -o $@ $^

clean:
	rm -f findpath *.o

provide:
	provide comp15 rt README Makefile c15.txt data0.txt ta.txt ec0.adat \
					findpath.cpp Graph.cpp Graph.h Node.h Stack_var.h \
					testGraph.cpp

# Add some rules for rt website
include Makefile.publish
