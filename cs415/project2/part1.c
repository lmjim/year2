/* Name: Lily Jim
 * DuckID: ljim
 * Assignment: CIS 415 Project 2
 * This is my own work with the execption of pseudocode provided in lab.
 */

#include <stdio.h>
#include <stdlib.h>
#include "bounded_queue.h"
#include "thread_safe_bounded_queue.h"
#include "topic_queue.h"

#define MAXENTRIES 5 // arbitrary limit
#define MAXTOPICS 2 // arbitrary limit

void fill(TopicQueue **topics, int entrynum, int pubID){
	 printf("Filling Queues\n");
	 int entrynum1 = entrynum;
	 int entrynum2 = entrynum;
	 int pubID1 = pubID;
	 int pubID2 = pubID;
         int i = 0;
         for(; i < MAXENTRIES; i++){
                 TopicEntry *item1 = InitEntry(entrynum1++, pubID1++, "https://unsplash.com/photos/rN3dqzDrhdk", "Duck standing in water");
                 Enqueue(topics[0], item1);
						                 
                 TopicEntry *item2 = InitEntry(entrynum2++, pubID2++, "https://clearcreekcounty.org/beaver/", "Beaver laying in water");
		 Enqueue(topics[1], item2);
         }
         printf("Topic 1 Entry Count: %d\n", GetCount(topics[0]));
         printf("Topic 2 Entry Count: %d\n", GetCount(topics[1]));
	 return;
}

int getAll(TopicQueue **topics, int lastentry){
	printf("Getting Entries:\n");
	int lastentry1 = lastentry;
	int lastentry2 = lastentry;
	while(lastentry1 <= GetFront(topics[0])){
	        TopicEntry *t = InitEntry(-1, -1, "", "");
		printf("Topic Queue 1:\n");
	        lastentry1 = GetEntry(topics[0], lastentry1, t);
	        PrintEntry(t);
		printf("Topic Queue 2:\n");
		lastentry2 = GetEntry(topics[1], lastentry2, t);
                PrintEntry(t);
	}
	return lastentry1;
}

void drain(TopicQueue **topics){
	printf("Draining Queues\n");
	while(GetCount(topics[0]) > 0){
		Dequeue(topics[0], GetBack(topics[0]), 1000);
		Dequeue(topics[1], GetBack(topics[1]), 1000);
	}
	printf("Topic 1 Entry Count: %d\n", GetCount(topics[0]));
        printf("Topic 2 Entry Count: %d\n", GetCount(topics[1]));
	return;
}

int main(){
	// Init and Malloc
	TopicQueue **topics = InitTopics(MAXTOPICS);
	topics[0] = MallocTopicQueue(MAXENTRIES, 1, "Topic 1");
	topics[1] = MallocTopicQueue(MAXENTRIES, 2, "Topic 2");
	TopicQueue *topic1 = topics[0];
	TopicQueue *topic2 = topics[1];
	printf("Topic Queues Generated\n");

	// Fill queues
	int entrynum = 1;
	int pubID = 1;
	fill(topics, entrynum, pubID);
	entrynum += 5;
	pubID += 5;

	// Get a few entries then dequeue
	int lastentry = 0;
	printf("Getting Entries:\n");
        int lastentry1 = lastentry;
        int lastentry2 = lastentry;
	int i = 0;
        for(; i<2; i++){
                TopicEntry *t = InitEntry(-1, -1, "", "");
                printf("Topic Queue 1:\n");
                lastentry1 = GetEntry(topics[0], lastentry1, t);
                PrintEntry(t);
                printf("Topic Queue 2:\n");
                lastentry2 = GetEntry(topics[1], lastentry2, t);
                PrintEntry(t);
	}
	lastentry = lastentry1;
	printf("\nKeeping track of lastentry: %d\n\n", lastentry);

	drain(topics);

	// Fill queues again
	fill(topics, entrynum, pubID);
        entrynum += 5;
        pubID += 5;

	// Get all the entries using the last entry recorded
	lastentry = getAll(topics, lastentry);

	// Attempt to access non-existent entry
	lastentry1 = lastentry;
	lastentry2 = lastentry;
	printf("\nKeeping track of lastentry: %d\n", lastentry);
	printf("Attempting to get non-existent entry. Should get front instead.\n");
	TopicEntry *t = InitEntry(-1, -1, "", "");
        printf("Topic Queue 1:\n");
        lastentry1 = GetEntry(topics[0], lastentry1, t);
        PrintEntry(t);
        printf("Topic Queue 2:\n");
        lastentry2 = GetEntry(topics[1], lastentry2, t);
        PrintEntry(t);
	lastentry = lastentry1;
	printf("Keeping track of lastentry: %d\n\n", lastentry);

	// Attempt to overfill queues
	printf("Attempting to add another entry.\n");
	TopicEntry *item = InitEntry(entrynum++, pubID++, "https://unsplash.com/photos/rN3dqzDrhdk", "Duck standing in water");
        int result = Enqueue(topics[0], item);
	if(result == -1){
		printf("Queue full. Nothing added.\n");
	}
	printf("Topic 1 Entry Count: %d\n", GetCount(topics[0]));

	drain(topics);

	// Attemp to underfill queues
	printf("Attempting to remove another entry.\n");
	result = Dequeue(topics[0], GetBack(topics[0]), 1000);
	if(result == 0){
		printf("Queue Empty. Nothing Removed.\n");
	}
	printf("Topic 1 Entry Count: %d\n", GetCount(topics[0]));

	// Free
	FreeTopicQueue(topic1);
	FreeTopicQueue(topic2);
	free(topics);
	printf("Topics Freed\n");
	return 0;
}
