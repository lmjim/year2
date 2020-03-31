#ifndef TOPIC_QUEUE_H
#define TOPIC_QUEUE_H

/* Name: Lily Jim
 * DuckID: ljim
 * Assignment: CIS 415 Project 2
 * This is my own work with the execption of pseudocode provided in lab.
 */

#define QUACKSIZE 2000 // common url limit
#define CAPTIONSIZE 280 // Tweet character limit

typedef struct{
	int entrynum;
        struct timeval timestamp;
        int pubID;
        char photoUrl[QUACKSIZE];
        char photoCaption[CAPTIONSIZE];
}TopicEntry;

TopicEntry *InitEntry(int entrynum, int pubID, char *url, char *caption);

void PrintEntry(TopicEntry *item);


typedef struct{
        TSBoundedQueue *queue;
        int id;
	int size;
	int lastentry;
        char name[250]; // arbitrary character limit
	pthread_mutex_t lock;
}TopicQueue;

TopicQueue **InitTopics(long size);

TopicQueue *MallocTopicQueue(long size, int id, char *name);

long long Enqueue(TopicQueue *queue, void *item);

int GetEntry(TopicQueue *queue, int lastentry, TopicEntry *t);

int Dequeue(TopicQueue *queue, long long id, int delta);

int GetCount(TopicQueue *queue);

long long GetFront(TopicQueue *queue);

long long GetBack(TopicQueue *queue);

int IsEmpty(TopicQueue *queue);

void FreeTopicQueue(TopicQueue *queue);

#endif
