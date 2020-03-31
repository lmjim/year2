Name: Lily Jim  
Date: 6/9/2019  
Class: CIS 415  

---

## Part 1

Files needed:

1. bounded\_queue.c and bounded\_queue.h  
   + The provided skeleton code has been filled in to create a working bounded queue  
2. thread\_safe\_bounded\_queue.c and thread\_safe\_bounded\_queue.h  
   + These files were left unchanged. They call the bounded queue functions in a thread safe manner  
3. topic\_queue.c and topic\_queue.h  
   + This file implements the topic queue and topic entry structures  
   + Enqueue, GetEntry, and Dequeue are defined in this file  
   + There are also additional topic queue functions that call on existing thread safe bounding queue functions such as GetFront and GetBack  
4. part1.c  
   + This file contains the main function to test part 1  
   + First two TopicQueues are created and filled  
   + A couple entries are retrieved then the queues are drained  
   + The queues are refilled and all of the entries are retrieved  
   + This continues from the recorded lastentry received from the prior fill/drain  
   + It also tries to getEntry ahead of the queued entries  
   + Then it attempts to overfill a queue, drains, and attempts to underfill a queue  
   + Finally the queues are freed  

**To test the code:**  
```
make part1
./part1
```

BoundedQueue also works with provided test files:  
bq\_test\_main.c and ts\_bq\_test\_main.c
```
make bq_test
./bq_test publisher_example.txt
./bq_test subscriber_example.txt
make ts_bq_test
./ts_bq_test publisher_example.txt
./ts_bq_test subscriber_example.txt
```
Note: the thread safe test file does not actually test anything.

---

## Part 2

Files needed:

1. part2.c  
   + This file contains the main function that creates and joins threads  
   + It also has the publisher, subscriber, and cleanup structs and functions  
   + Part 2 is essentially practice with threading  
   + Per "Project 2 Rubric" the threads simply print a unique string and do not do anything with queues  
   + Note: if more implementation was actually needed, please refer to part 3 or later

**To test the code:**
```
make part2
./part2
```

---

## Part 3

Files needed:

1. Files listed under points 1, 2, and 3 from Part 1  
2. command\_input.txt  
   + This file contains the example command input that was posted on Piazza  
3. part3.c  
   + This file contains the main function that reads commands in from a file to create topic queues and threads  
   + Main reads in all of the commands, then, right after creating the cleanup thread, starts the publishers and subscribers  
   + Main finishes after all of the threads have joined again

**To test the code**:
```
make part3
./part3 command_input.txt
```

---

## Part 4

Files needed:

1. Files listed under points 1, 2, and 3 from Part 1  
2. my\_command\_input.txt  
   + This file contains commands to create topics and threads  
   + It has 2 topics of their exact needed size, 1 topic with a larger size, and 1 topic with too small of a size  
   + This allows for testing of the looping queue and making sure there are not errors when you do not fill the entire allocated space  
   + The commands start 4 publishers and 3 subscribers, see point 3
3. ducks\_publisher.txt, ducks\_subscriber.txt, football\_publisher.txt, football\_subscriber.txt, trophies\_publisher.txt, awards\_publisher.txt, remaining\_subscriber.txt  
   + These files are called upon through the my\_command\_input.txt file  
   + The publisher files were made with the help of Matt's [img\_url\_crawler](https://github.com/mattall/img_url_crawler)  
4. part4.c  
   + This file contains the main function that reads commands in from a file to create topic queues and threads  
   + This file is different from part3.c because the thread functions have changed  
   + Now the publisher, subscriber, and cleanup actually call upon enqueue, getItem, and dequeue  
   + Publishers will keep trying to enqueue until it can, this prevents a loss of posts  
   + Subscribers, upon no new entries, will keep trying for 5 seconds and if there are still no new posts, it will continue on  
   (This leaves the potential open for some posts to get lost if they take a long time to get queued)  
   + Subscribers also write out information to an output.txt file based on the information they receive  
   + The cleanup thread will repeatedly attempt to dequeue, if DELTA is met, the item actually gets dequeued  
   + Cleanup also listens for a signal to indicate that publishers and subscribers are done, when they are, the cleanup thread makes sure to drain all of the queues before exiting

**File produced:**  
This program produces output.txt  
It is written to append to the end of the file, so make sure output.txt is empty/does not exist before running  
The 'make clean' command will remove output.txt

**To test the code:**
```
make part4
./part4 my_command_input.txt
```

Note: lastentry was not a part of the topic queue structure until this part, hence part 1 keeps track of lastentry within main itself

---

## Part 5

Files needed:

1. Files listed under points 1, 2, and 3 from Part 4  
2. part5.c  
   + This file is extremely similar to part4.c but produces html files instead of one singular txt file  
   + Unlike the txt file, the html file needs a chunk of code in the beginning prior to what the subscribers add, so there is another function to do this  
   + To keep track of each topic's html file, a global variable was created  
   + Before freeing variables, the last couple lines of the files are appended after the subscribers have entered their information to the files

**Files produced:**  
This program produces one html file for every subscriber  
The html file is saved under the exact same name as the subscriber file but as a .html instead of a .txt  
They can be opened in Firefox on the VM  
Using my\_command\_input.txt there are 3 html files produced  
```
ducks_subscriber.html
football_subscriber.html
remaining_subscriber.html
```

**To test the code:**  
```
make part5
./part5 my_command_input.txt
```

---

## Grading

All files have been tested on the provided Arch Linux distribution for CIS 415 Spring 2019.
Parts 1, 2, 3, 4, and 5 are all fully implemented.  
The provided Makefile is compatible with each part.  
To compile all files at once, simply run:
```
make
```
Also, as requested, the executables are already provided as well.  
Before running part4, you should remove output.txt as it concatenates.  
The .html files should also be removed before running part5 to avoid any issues.  

