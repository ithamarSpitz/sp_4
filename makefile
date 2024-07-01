#itas12@gmail.com
CXXFLAGS = -std=c++11 -fPIC -pthread

tree: main.o Complex.o Tree.o
	g++ $(CXXFLAGS) main.o Complex.o Tree.o -o main
	./main

main.o: main.cpp Tree.hpp Complex.hpp
	g++ $(CXXFLAGS) -c main.cpp

demo: demo.o Complex.o
	g++ $(CXXFLAGS) demo.o Complex.o -o demo
	./demo

demo.o: demo.cpp Tree.hpp Complex.hpp
	g++ $(CXXFLAGS) -c demo.cpp

tests: tests.o Complex.o
	g++ $(CXXFLAGS) tests.o Complex.o -o tests
	./tests

tests.o: tests.cpp Tree.hpp Complex.hpp
	g++ $(CXXFLAGS) -c tests.cpp

Complex.o: Complex.cpp Complex.hpp
	g++ $(CXXFLAGS) -c Complex.cpp

Tree.o: Tree.cpp Tree.hpp
	g++ $(CXXFLAGS) -c Tree.cpp

clean:
	rm -f *.o *.svg demo tests main
