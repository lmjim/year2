/* Name: Lily Jim
 * DuckID: ljim
 * Assignment: CIS 415 Project 2
 * This is my own work based off of an example provided.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <pthread.h>
#include "bounded_queue.h"
#include "thread_safe_bounded_queue.h"
#include "topic_queue.h"

TopicEntry *InitEntry(int entrynum, int pubID, char *url, char *caption){
	TopicEntry *returnValue = NULL;
	returnValue = (TopicEntry *)malloc(sizeof(TopicEntry));
	returnValue->entrynum = entrynum;
	gettimeofday(&returnValue->timestamp, NULL);
	returnValue->pubID = pubID;
	strcpy(returnValue->photoUrl, url);
	strcpy(returnValue->photoCaption, caption);
	return (TopicEntry *)returnValue;
}

void PrintEntry(TopicEntry *item){
	if(item != NULL){
		printf("Got Entry: %d\n\tID: %d\n\tUrl: %s\n\tCaption: %s\n\tTimestamp: %ld\n", item->entrynum, item->pubID, item->photoUrl, item->photoCaption, item->timestamp.tv_usec);
	}
	else{
		printf("Whoops! Tried to print a non-existent item!\n");
	}
	return;
}


TopicQueue **InitTopics(long size){
	TopicQueue **returnValue = NULL;
	returnValue = calloc(size, sizeof(TopicQueue*));
	return returnValue;
}

TopicQueue *MallocTopicQueue(long size, int id, char *name){
	TopicQueue *returnValue = NULL;
	returnValue = (TopicQueue *)malloc(sizeof(TopicQueue));
	returnValue->queue = TS_BB_MallocBoundedQueue(size);
	returnValue->id = id;
	returnValue->size = size;
	returnValue->lastentry = 0;
	strcpy(returnValue->name, name);
	pthread_mutex_init(&(returnValue->lock), NULL);
	return returnValue;
}

long long Enqueue(TopicQueue *queue, void *item){
	long long returnValue = -1;
	returnValue = TS_BB_TryEnqueue(queue->queue, item);
	return returnValue;
}

int GetEntry(TopicQueue *queue, int lastentry, TopicEntry *t){
	// Using the lock here because memcpy happens outside the TS_BB lock
	int returnValue = -1;
	if(TS_BB_IsEmpty(queue->queue)){
		return 0;
	}
	pthread_mutex_lock(&(queue->lock)); 
	if(TS_BB_IsIdValid(queue->queue, lastentry)){
		memcpy(t, TS_BB_GetItem(queue->queue, lastentry), sizeof *t);
		pthread_mutex_unlock(&(queue->lock));
		return lastentry + 1;
	}
	long long tail = TS_BB_GetBack(queue->queue);
	if(tail > lastentry){
		memcpy(t, TS_BB_GetItem(queue->queue, tail), sizeof *t);
		pthread_mutex_unlock(&(queue->lock));
		return tail + 1;
	}
	long long front = TS_BB_GetFront(queue->queue);
	if(front < lastentry){
		memcpy(t, TS_BB_GetItem(queue->queue, front), sizeof *t);
		pthread_mutex_unlock(&(queue->lock));
		return front + 1;
	}
	pthread_mutex_unlock(&(queue->lock));
	return returnValue;
}

int Dequeue(TopicQueue *queue, long long id, int delta){
	int returnValue = 0;
	if(TS_BB_IsEmpty(queue->queue)){
                return returnValue;
        }
	pthread_mutex_lock(&(queue->lock));
	struct timeval timestamp;
	gettimeofday(&timestamp, NULL);
	TopicEntry *t = InitEntry(-1, -1, "", "");
	memcpy(t, TS_BB_GetItem(queue->queue, id), sizeof *t);
	long diff = timestamp.tv_usec - (t->timestamp.tv_usec);
	if(delta < diff){
		// only dequeue if aged past delta
		returnValue = TS_BB_TryDequeue(queue->queue, id);
	}
	free(t);
	pthread_mutex_unlock(&(queue->lock));
	return returnValue;
}

int GetCount(TopicQueue *queue){
	return TS_BB_GetCount(queue->queue);
}

long long GetFront(TopicQueue *queue){
        return TS_BB_GetFront(queue->queue);
}

long long GetBack(TopicQueue *queue){
	return TS_BB_GetBack(queue->queue);
}

int IsEmpty(TopicQueue *queue){
	return TS_BB_IsEmpty(queue->queue);
}

void FreeTopicQueue(TopicQueue *queue){
	free(queue->queue);
	pthread_mutex_destroy(&(queue->lock));
	free(queue);
}
