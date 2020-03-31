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
#include <unistd.h>
#include <sys/time.h>

#include "bounded_queue.h"
#include "thread_safe_bounded_queue.h"
#include "topic_queue.h"

#define MAXENTRIES 99 // arbitrary limit
#define MAXTOPICS 5 // arbitrary limit
#define NUMPROXIES 10 // arbitrary limit

// Global
TopicQueue **topics;
char **htmls;
int DELTA = 0;
int SIGNAL = 0;

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
	
        FILE *in = fopen(pub->filename, "r"); // will need to close file
        if(in == NULL){
                // issue opening file
                printf("Error: issue opening file\n");
                exit(1);
        }
	char *line = NULL; // getline will allocate memory, will need to be freed
        size_t len = 0;
        ssize_t chars;
	int entrynum = 1;
        while((chars = getline(&line, &len, in)) != -1){
		// init entry
		int pubID = line[0] - '0';
		chars = getline(&line, &len, in);
		char *url = strdup(line);
		chars = getline(&line, &len, in);
		char *caption = strdup(line);
		// enqueue
		TopicEntry *item = InitEntry(entrynum++, pubID, url, caption);
		int result = -1;
		while(result == -1){
			result = Enqueue(topics[pubID], item);
		}
		// sleep
		chars = getline(&line, &len, in);
		int sleep_time = line[0] - '0';
		sleep(sleep_time);
		printf("Item enqueued (%d:%d)\n", pubID, entrynum);
	}
	free(line);
	fclose(in);

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

	FILE *in = fopen(sub->filename, "r");
	if(in == NULL){
                // issue opening file
                printf("Error: issue opening file\n");
                exit(1);
        }
	FILE *out = fopen(htmls[sub->thread_num-1], "a"); // append instead of write (starting at top of file each time)
	if(out == NULL){
		printf("Error: issue opening %s\n", htmls[sub->thread_num]);
		exit(1);
	}
	char *line = NULL; // getline will allocate memory, will need to be freed
        size_t len = 0;
        ssize_t chars;
	while((chars = getline(&line, &len, in)) != -1){
		int id = line[0] - '0';
		// GetEntry
		TopicEntry *t = InitEntry(-1, -1, "", "");
		int lastentry = GetEntry(topics[id], topics[id]->lastentry, t);
		if(lastentry == topics[id]->lastentry){
			struct timeval start;
			gettimeofday(&start, NULL);
			while((lastentry = GetEntry(topics[id], topics[id]->lastentry, t)) == topics[id]->lastentry){
				struct timeval end;
				gettimeofday(&end, NULL);
				if((end.tv_sec - start.tv_sec) > 5){
					break; // Don't run this loop infinetly, wait max 5 seconds
				}
			}
		}
		else{
			fprintf(out, "<hr>\n<img SRC=\"%s\"></a><br>\n%s\n<hr>\n", t->photoUrl, t->photoCaption);
			topics[id]->lastentry = lastentry;
		}
		free(t);
		// sleep
		chars = getline(&line, &len, in);
		int sleep_time = line[0] - '0';
		sleep(sleep_time);
		printf("Item retrieved (%d:%d)\n", id, t->entrynum);
	}
	free(line);
	fclose(in);
	fclose(out);

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
	sleep(5);
	while(!SIGNAL){
		int i = 0;
		for(;i<MAXTOPICS;i++){
			if(topics[i] != 0){
				printf("Attempting to dequeue (%d)\n", i);
				long long tail = GetBack(topics[i]);
				Dequeue(topics[i], tail, DELTA); // Dequeue itself checks aging
			}
		}
		sleep(2);
	}
	printf("Cleanup received signal\n");
	// publisher and subscribers are done, drain each queue
	int i = 0;
	for(;i<MAXTOPICS;i++){
		if(topics[i] != 0){
			while(!IsEmpty(topics[i])){
				long long tail = GetBack(topics[i]);
	                        Dequeue(topics[i], tail, DELTA); 
			}
			printf("Drained (%d)\n", i);
		}
	}
	printf("Queues drained\n");
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

// HTML
char *create_html(char *name, int sub_num){
	int len = strlen(name);
	char *html = (char *)malloc((len + 3) * sizeof(char));
	int i = 0;
	for(;i<len-3;i++){
		html[i] = name[i]; // copy everything but txt (keeps '.')
	}
	html[i++] = 'h';
	html[i++] = 't';
	html[i++] = 'm';
	html[i++] = 'l';
	html[i++] = 0;
	
	FILE *out = fopen(html, "w"); // always want to start at the beginning here
        if(out == NULL){
                printf("Error: issue opening html file for subscriber %d\n", sub_num);
                exit(1);
        }
	fprintf(out, "<!DOCTYPE html>\n<html>\n<head>\n<body>\n<table>\n\t<tr>\n\t<td align=\"left\">\n\t\t<img SRC=\"http://3.bp.blogspot.com/-9bmVJgSfEZc/VgA_iPcnrTI/AAAAAAAAGQA/wS8FSQcL9Gs/s1600/The_Oregon_Duck_2.jpg\" WIDTH=\"140\" HEIGHT=\"140\">&nbsp&nbsp&nbsp&nbsp&nbsp</a>\n\t</td>\n\t<td align=\"center\">\n\t\t<h1>InstaQuack</h1>\n\t\t<h1>Subscriber %d: Topic %s</h1>\n\t</td>\n\t<td align=\"right\">\n\t\t&nbsp&nbsp&nbsp&nbsp&nbsp<img SRC=\"http://3.bp.blogspot.com/-9bmVJgSfEZc/VgA_iPcnrTI/AAAAAAAAGQA/wS8FSQcL9Gs/s1600/The_Oregon_Duck_2.jpg\" WIDTH=\"140\" HEIGHT=\"140\"></a>\n\t</td>\n</tr>\n</table>\n", sub_num+1, topics[sub_num]->name);
	fclose(out);

	return html;
}

// Server
int main(int argc, char **argv){
	topics = InitTopics(MAXTOPICS);
	int topic_num = 0;
	htmls = (char **)malloc(MAXTOPICS * sizeof(char *));
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
							char *html = create_html(name, sub_num);
                                                        htmls[sub_num] = strdup(html);
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
	SIGNAL = 1; // let cleanup know that publishers and subscribers are done
	void *ret = NULL;
	pthread_join(cleanup, &ret);
	printf("dequeue thread exited\n");

	// finish html files
	int i = 0;
        for(;i<sub_num;i++){
                FILE *out = fopen(htmls[i], "a"); // append instead of write (starting at top of file each time)
                if(out == NULL){
                        printf("Error: issue opening html file for subscriber %d\n", i);
                        exit(1);
                }
                fprintf(out, "</body>\n</html>\n");
                fclose(out);
        }

	// free
	free(pub_info);
	free(sub_info);
	i = 0;
	for(;i<sub_num;i++){
		free(htmls[i]);
	}
	free(htmls);
	i = 0;
	for(;i<MAXTOPICS;i++){
		if(topics[i] != 0){
			FreeTopicQueue(topics[i]);
		}
	}
	free(topics);
	return 0;
}

