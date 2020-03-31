CC = gcc
CFLAGS = -g -Wall
LIBS = -lm

all: tester part1 part2 part3 part4 part5 iobound cpubound

# note: to run all tests use < ./fullTest.sh >
run: all clean fullTest.sh
	make all
	./fullTest.sh
	make clean

tester: tester.c
	$(CC) $(CFLAGS) $^ -o $@

part1: part1.h part1.c
	$(CC) $(CFLAGS) $^ -o $@

part2: part2.h part2.c
	$(CC) $(CFLAGS) $^ -o $@

part3: part3.h part3.c
	$(CC) $(CFLAGS) $^ -o $@

part4: part4.h part4.c
	$(CC) $(CFLAGS) $^ -o $@

part5: part5.h part5.c
	$(CC) $(CFLAGS) $^ -o $@

iobound: iobound.c
	$(CC) $(CFLAGS) $^ -o $@

cpubound: cpubound.c
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS)

clean:
	-rm tester
	-rm part1
	-rm part2
	-rm part3
	-rm part4
	-rm part5
	-rm iobound
	-rm cpubound
