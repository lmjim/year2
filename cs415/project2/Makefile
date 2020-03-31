# Name: Lily Jim
# DuckID: ljim
# Assignment: CIS 415 Project 2
# With the exception of the starter code provided, this is my own work.

CC=gcc
LIBS=-lpthread -lm 
CFLAGS=-g -Wall -std=gnu99
OBJECTS=bounded_queue.o thread_safe_bounded_queue.o topic_queue.o utilities.o

PROGRAMS=bq_test ts_bq_test part1 part2 part3 part4 part5

all: $(PROGRAMS)
objects: $(OBJECTS)

bq_test: utilities.o bounded_queue.o bq_test_main.c
	$(CC) -o bq_test $(CFLAGS) bq_test_main.c utilities.o bounded_queue.o $(LIBS)

ts_bq_test: utilities.o thread_safe_bounded_queue.o ts_bq_test_main.c
	$(CC) -o ts_bq_test $(CFLAGS) ts_bq_test_main.c utilities.o bounded_queue.o thread_safe_bounded_queue.o $(LIBS)

part1: part1.c topic_queue.o thread_safe_bounded_queue.o bounded_queue.o
	$(CC) -o $@ $(CFLAGS) $^ $(LIBS)

part2: part2.c
	$(CC) -o $@ $(CFLAGS) $^ $(LIBS)

part3: part3.c topic_queue.o thread_safe_bounded_queue.o bounded_queue.o
	$(CC) -o $@ $(CFLAGS) $^ $(LIBS)

part4: part4.c topic_queue.o thread_safe_bounded_queue.o bounded_queue.o
	$(CC) -o $@ $(CFLAGS) $^ $(LIBS)

part5: part5.c topic_queue.o thread_safe_bounded_queue.o bounded_queue.o
	$(CC) -o $@ $(CFLAGS) $^ $(LIBS)

bounded_queue.o: bounded_queue.c bounded_queue.h
thread_safe_bounded_queue.o: thread_safe_bounded_queue.c thread_safe_bounded_queue.h
topic_queue.o: topic_queue.c topic_queue.h
utilities.o: utilities.c utilities.h

clean:
	rm -f *.o $(PROGRAMS) output.txt
