QTFLAGS = -DQT_WIDGETS_LIB -DQT_GUI_LIB -DQT_CORE_LIB -I/usr/include/x86_64-linux-gnu/qt5/QtWidgets -I/usr/include/x86_64-linux-gnu/qt5 -I/usr/include/x86_64-linux-gnu/qt5/QtGui -I/usr/include/x86_64-linux-gnu/qt5 -I/usr/include/x86_64-linux-gnu/qt5/QtCore -I/usr/include/x86_64-linux-gnu/qt5
QTLIBS = -lQt5Widgets -lQt5Gui -lQt5Core -pthread
CXXFLAGS = -std=c++11 -fPIC  -pthread

tree: main.o Complex.o Tree.o
	g++ $(CXXFLAGS) main.o Complex.o Tree.o -o main $(QTLIBS)
	./main

main.o: main.cpp Tree.hpp Complex.hpp
	g++ $(CXXFLAGS) $(QTFLAGS) -c main.cpp

demo: demo.o Complex.o
	g++ $(CXXFLAGS) demo.o Complex.o -o demo $(QTLIBS)

demo.o: demo.cpp Tree.hpp Complex.hpp
	g++ $(CXXFLAGS) $(QTFLAGS) -c demo.cpp

tests: tests.o Complex.o
	g++ $(CXXFLAGS) tests.o Complex.o -o tests $(QTLIBS)

tests.o: tests.cpp Tree.hpp Complex.hpp
	g++ $(CXXFLAGS) $(QTFLAGS) -c tests.cpp

Complex.o: Complex.cpp Complex.hpp
	g++ $(CXXFLAGS) -c Complex.cpp

Tree.o: Tree.cpp Tree.hpp
	g++ $(CXXFLAGS) -c Tree.cpp

clean:
	rm -f *.o *.svg demo tests main
