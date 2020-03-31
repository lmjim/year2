# very basic Makefile to compile and remove reversi

reversi: reversi.hpp reversi.cpp placement.hpp placement.cpp flip.hpp flip.cpp main.cpp
	g++ -g -std=c++14 -o reversi reversi.cpp placement.cpp flip.cpp main.cpp

clean:
	rm reversi
