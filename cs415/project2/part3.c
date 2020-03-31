/* Name: Lily Jim
 * DuckID: ljim
 * Assignment: CIS 415 Project 2
 * This is my own work with the exception of the code taken from
 * 	part1 and part2. Please refer to those credits.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#include "bounded_queue.h"
#include "thread_safe_bounded_queue.h"
#include "topic_queue.h"

#define MAXENTRIES 99 // arbitrary limit
#define MAXTOPICS 5 // arbitrary limit
#define NUMPROXIES 10 // arbitrary limit

// Global
TopicQueue **topics;
int DELTA = 0;

// Publishers
struct publisher_info{
        pthread_t tid;
        int thread_num;
        char filename[250];
	int wait;
};
void *publisher_start(void *pub_info){
        struct publisher_info *pub = pub_info;
	while(pub->wait == 1){}
        printf("publisher thread %d reading from %s\n", pub->thread_num, pub->filename);
        return NULL;
}
void publisher_query(struct publisher_info *pub_info){
	int i = 0;
	for(;i<NUMPROXIES;i++){
		if(pub_info[i].thread_num != 0){ // if it is 0 then that publisher does not actually exist
			printf("publisher thread %d %s\n", pub_info[i].thread_num, pub_info[i].filename);
		}
		else{
			break;
		}
	}
	return;
}

// Subscribers
struct subscriber_info{
        pthread_t tid;
        int thread_num;
        char filename[250];
	int wait;
};
void *subscriber_start(void *sub_info){
        struct subscriber_info *sub = sub_info;
	while(sub->wait == 1){}
	printf("subscriber thread %d reading from %s\n", sub->thread_num, sub->filename);
	return NULL;
}
void subscriber_query(struct subscriber_info *sub_info){
	int i = 0;
        for(;i<NUMPROXIES;i++){
                if(sub_info[i].thread_num != 0){
                        printf("subscriber thread %d %s\n", sub_info[i].thread_num, sub_info[i].filename);
                }
		else{
			break;
		}
        }
        return;
}

// Cleanup
void *cleanup_start(void *none){
	printf("dequeue thread created\n");
	return NULL;
}

// Topics
void topic_query(){
	int i = 0;
	for(;i<MAXTOPICS;i++){
		if(topics[i] != 0){
			printf("topic %d %d\n", topics[i]->id, topics[i]->size);
		}
		else{
			break;
		}
	}
}

// Threads
void start_threads(struct publisher_info *pub_info, struct subscriber_info *sub_info){
	int i = 0;
	for(;i<NUMPROXIES;i++){
		if(pub_info[i].thread_num != 0){
			pub_info[i].wait = 0;
		}
		else{
			break;
		}
	}
	i = 0;
        for(;i<NUMPROXIES;i++){
                if(sub_info[i].thread_num != 0){
			sub_info[i].wait = 0;
                }
                else{
                        break;
                }
        }
        return;
}
void join_threads(struct publisher_info *pub_info, struct subscriber_info *sub_info){
	void *ret = NULL;
	int i = 0;
        for(;i<NUMPROXIES;i++){
                if(pub_info[i].thread_num != 0){
			int id = pub_info[i].thread_num;
                        pthread_join(pub_info[i].tid, &ret);
			printf("publisher thread %d Exited\n", id);
                }
                else{
                        break;
                }
	}
        i = 0;
        for(;i<NUMPROXIES;i++){
                if(sub_info[i].thread_num != 0){
			int id = sub_info[i].thread_num;
                        pthread_join(sub_info[i].tid, &ret);
			printf("subscriber thread %d Exited\n", id);
                }
                else{
	                break;
                }
        }
	if(ret != NULL){
		free(ret);
	}
	return;
}

// Server
int main(int argc, char **argv){
	topics = InitTopics(MAXTOPICS);
	int topic_num = 0;
	struct publisher_info *pub_info = calloc(NUMPROXIES, sizeof(struct publisher_info));
	int pub_num = 0;
	struct subscriber_info *sub_info = calloc(NUMPROXIES, sizeof(struct subscriber_info));
	int sub_num = 0;
	pthread_t cleanup;

	// Read file
	if(argc != 2){
                // no file to read from
                printf("Error: no file to read from or too many args given\n");
                exit(1);
        }
	FILE *in = fopen(argv[1], "r"); // will need to close file
        if(in == NULL){
                // issue opening file
                printf("Error: issue opening file\n");
                exit(1);
        }
        char *line = NULL; // getline will allocate memory, will need to be freed
        size_t len = 0;
        ssize_t chars;
        while((chars = getline(&line, &len, in)) != -1){
		if(chars > 1){
		char firstWord = line[0];
		char secondWord = 0;
		int id = -1;
		int size = -1;
		char *name = NULL;
		int num = chars - 6;
		char number[15];
		int i = 0;
		switch(firstWord){
			case 'c':
				secondWord = line[7];
				switch(secondWord){
					case 't':
						if(topic_num >= MAXTOPICS){
							printf("Oh No! You've exceeded the max number of topics\n");
						}
						else{
							// since MAXENTRIES is 99, it should only be one or 2 digits
							if(line[chars - 3] == ' '){
								size = line[chars-2] - '0';
								num = chars - 18; 
								name = (char *)malloc(num * sizeof(char));
								for(;i<num-1;i++){
									name[i] = line[i + 16];
								}
								name[num-1] = 0;
							}
							else{
								size = line[chars-3] - '0';
								size = size * 10;
								size = size + (line[chars-2] - '0');
								num = chars - 19;
								name = (char *)malloc(num * sizeof(char));
								for(;i<num-1;i++){
									name[i] = line[i+16];
								}
								name[num-1] = 0;
							}
							// since MAXTOPICS is 5, it should only be one digit
							id = line[13] - '0';
							topics[topic_num] = MallocTopicQueue(size, id, name);
							topic_num++;
						}
						break;
					case 'p':
						if(pub_num >= NUMPROXIES){
							printf("Oh No! You've exceeded the max number of publishers\n");
						}
						else{
							num = chars - 19;
							name = (char *)malloc(num * sizeof(char));
							for(;i<num-1;i++){
								name[i] = line[i+18];
							}
							name[num-1] = 0;
							pub_info[pub_num].thread_num = pub_num + 1;
							strcpy(pub_info[pub_num].filename, name);
							pub_info[pub_num].wait = 1;
							pthread_create(&pub_info[pub_num].tid, NULL, &publisher_start, &pub_info[pub_num]);
							pub_num++;
						}
						break;
					case 's':
						if(sub_num >= NUMPROXIES){
							printf("Oh No! You've exceeded the max number of subscribers\n");
						}
						else{
							num = chars - 20;
							name = (char *)malloc(num * sizeof(char));
							for(;i<num-1;i++){
								name[i] = line[i+19];
							}
							name[num-1] = 0;
							sub_info[sub_num].thread_num = sub_num + 1;
							strcpy(sub_info[sub_num].filename, name);
							sub_info[sub_num].wait = 1;
							pthread_create(&sub_info[sub_num].tid, NULL, &subscriber_start, &sub_info[sub_num]);
							sub_num++;
						}
						break;
					default:
						printf("Whoops! Something went wrong reading the second word\n");
						break;
				}
				break;
			case 'q':
				secondWord = line[6];
				switch(secondWord){
					case 't':
						topic_query();
						break;
					case 'p':
						publisher_query(pub_info);
						break;
					case 's':
						subscriber_query(sub_info);
						break;
					default:
						printf("Whoops! Something went wrong reading the second word\n");
						break;
				}
				break;
			case 'd':
				number[num] = 0;
				for(;i<num;i++){
					number[i] = line[6+i];
				}
				char *ptr;
				long d = strtol(number, &ptr, 10);
				DELTA = (int) d;
				break;
			case 's':
				pthread_create(&cleanup, NULL, &cleanup_start, NULL);
				start_threads(pub_info, sub_info);
				break;
			default:
				printf("Whoops! Something went wrong reading the first word\n");
				break;
		}
		}
        }

        free(line); // deallocate memory
        fclose(in); // close file

	join_threads(pub_info, sub_info);
	void *ret = NULL;
	pthread_join(cleanup, &ret);
	printf("dequeue thread exited\n");

	free(pub_info);
	free(sub_info);
	free(topics);
	return 0;
}

