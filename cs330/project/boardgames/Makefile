# Define some variables:
LIBS = -lncurses
CXX = g++
CXXFLAGS = -g -std=c++14

%.o: %.cpp
	$(CXX) -c $(CXXFLAGS) $<

main.exe: libboardGames.a main.o
	$(CXX) main.o -L. -lboardGames -o main.exe -lncurses

#main.exe: randMove.o input.o chessBoard.o sorryBoard.o aggravationBoard.o chess.o checkers.o sorry.o aggravation.o main.o
#	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIBS)

run: main.exe
	./main.exe

chessBoardTest.exe: chessBoard.o chessBoardTest.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIBS)

inputTest.exe: randMove.o input.o inputTest.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIBS)

helloWorld.exe: HelloWorldNCurses.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIBS)

library: randMove.o input.o chessBoard.o sorryBoard.o aggravationBoard.o chess.o checkers.o sorry.o aggravation.o
	ar rcs libboardGames.a $^

clean:
	rm *.o *.exe
