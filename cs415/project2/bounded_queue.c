/* Name: Lily Jim
 * DuckID: ljim
 * Assignment: CIS 415 Project 2
 * With the exception of the starter code provided, this is my own work.
 */

#include <stdio.h>
#include <stdlib.h>
#include "bounded_queue.h"

struct bounded_queue{
        int size;       // capacity
        void **buffer;  // storage
        long long head;
        long long tail;
}; // typedef in header as BoundedQueue

int RoundIDToBufferIndex(int size, long long index){
        long long value = (index % ((long long)size));
        return (int)value;
}

BoundedQueue *BB_MallocBoundedQueue(long size){
        struct bounded_queue *returnValue = NULL;
	returnValue = (struct bounded_queue*)malloc(sizeof(struct bounded_queue));
	returnValue->size = size; // keep track of size
	returnValue->buffer = (void **)malloc(size * sizeof(void *)); // be ready for items
	returnValue->head = 0; // initially start at 0
	returnValue->tail = 0; // initially start at 0
        return (BoundedQueue *)returnValue;
}

long long BB_TryEnqueue(struct bounded_queue *queue,void *item){
        long long returnValue = -1;
	if(!BB_IsFull(queue)){
		queue->buffer[RoundIDToBufferIndex(queue->size, queue->head)] = item;
		returnValue = queue->head;
		queue->head++;
	}
	return returnValue;
}

int BB_TryDequeue(struct bounded_queue *queue,long long id){
        int  returnValue = 0;
	if(queue->tail == id && !BB_IsEmpty(queue)){
		queue->buffer[RoundIDToBufferIndex(queue->size, queue->tail)] = NULL;
		queue->tail++;
		returnValue = 1;
	}
        return returnValue;
}

long long BB_GetFront(struct bounded_queue *queue){
        long long returnValue = -1;
        if(!BB_IsEmpty(queue)){
                returnValue = queue->head-1;
        }
        return returnValue;
}

long long BB_GetBack(struct bounded_queue *queue){
        long long returnValue = -1;
	if(!BB_IsEmpty(queue)){
		returnValue = queue->tail;
	}
        return returnValue;
}

int BB_GetCount(struct bounded_queue *queue){
        long long returnValue = 0;
	returnValue = queue->head - queue->tail;
        return (int)returnValue;
}

int BB_IsIdValid(struct bounded_queue *queue,long long id){
        int returnValue = 0; // False
	if(queue->tail <= id && id < queue->head){
		returnValue = 1; // True
	}
        return returnValue;
}

void *BB_GetItem(struct bounded_queue *queue,long long id){
        void *returnValue = NULL;
	if(BB_IsIdValid(queue, id)){
		returnValue = queue->buffer[RoundIDToBufferIndex(queue->size, id)];
	}
        return returnValue;
}

int BB_IsFull(struct bounded_queue *queue){
        int returnValue = 0; // False
	if(queue->size == BB_GetCount(queue)){
		returnValue = 1; // True
	}
        return returnValue;
}

int BB_IsEmpty(struct bounded_queue *queue){
        int returnValue = 0; // False
	if(queue->head == queue->tail){
		returnValue = 1; // True
	}
        return returnValue;
}

void BB_FreeBoundedQueue(struct bounded_queue *queue){
	free(queue->buffer);
	queue->buffer = NULL;
	queue->size = 0;
	queue->head = 0;
	queue->tail = 0;
	free(queue);
	return;
}

