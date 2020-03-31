CXX = g++
CXXFLAGS = -g -std=c++14

%.o: %.cpp
	$(CXX) -c $(CXXFLAGS) $<

all: testRot13cipher.exe testCaesar.exe testDate.exe

testRot13cipher.exe: testRot13cipher.o rot13cipher.o ioutils.o
	$(CXX) -o $@ $^

testCaesar.exe: caesar.o testCaesar.o ioutils.o
	$(CXX) $(CXXFLAGS) -o $@ $^

testDate.exe: date.o testDate.o ioutils.o
	$(CXX) $(CXXFLAGS) -o $@ $^

clean: 
	$(RM) *.o *.exe
