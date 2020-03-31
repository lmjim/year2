/* Name: Lily Jim
 * DuckID: ljim
 * Assignment: CIS 415 Project 2
 * This code is based off of the man page for pthread_create and pseudocode provided in lab.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

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
        printf("Thread #%d\tMessage: %s\n", pub->thread_num, pub->filename);
        return NULL;
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
	printf("Thread #%d\tMessage: %s\n", sub->thread_num, sub->filename);
	return NULL;
}

// Cleanup
struct cleanup_info{
	pthread_t tid;
	int thread_num;
	char filename[250];
	int wait;
};
void *cleanup_start(void *clean_info){
	struct cleanup_info *clean = clean_info;
	while(clean->wait == 1){}
	printf("Thread #%d\tMessage: %s\n", clean->thread_num, clean->filename);
	return NULL;
}

int main(){
	struct publisher_info *pub_info = NULL;
	struct subscriber_info *sub_info = NULL;
	int pub_num = 0;
	int sub_num = 0;
	int num_publishers = 2;
	int num_subscribers = 2;
	pub_info = calloc(num_publishers, sizeof(struct publisher_info));
	sub_info = calloc(num_subscribers, sizeof(struct subscriber_info));
	if(pub_info == NULL || sub_info == NULL){
		do{ perror("calloc"); exit(EXIT_FAILURE); } while (0);
	}

	// for both publishers
	pub_info[pub_num].thread_num = pub_num + 1;
	strcpy(pub_info[pub_num].filename, "First Publisher, Unique String");
	pub_info[pub_num].wait = 1;
	pthread_create(&pub_info[pub_num].tid, NULL, &publisher_start, &pub_info[pub_num]);

	pub_num++;
	pub_info[pub_num].thread_num = pub_num + 1;
        strcpy(pub_info[pub_num].filename, "Second Publisher, Unique String");
	pub_info[pub_num].wait = 1;
	pthread_create(&pub_info[pub_num].tid, NULL, &publisher_start, &pub_info[pub_num]);

	// for both subscribers
	sub_info[sub_num].thread_num = sub_num + 1;
	strcpy(sub_info[sub_num].filename, "First Subscriber, Unique String");
	sub_info[sub_num].wait = 1;
	pthread_create(&sub_info[sub_num].tid, NULL, &subscriber_start, &sub_info[sub_num]);

	sub_num++;
	sub_info[sub_num].thread_num = sub_num + 1;
        strcpy(sub_info[sub_num].filename, "Second Subscriber, Unique String");
	sub_info[sub_num].wait = 1;
	pthread_create(&sub_info[sub_num].tid, NULL, &subscriber_start, &sub_info[sub_num]);

	// for cleanup
	struct cleanup_info *clean_info = NULL;
	clean_info = calloc(1, sizeof(struct cleanup_info));
	clean_info[0].thread_num = 1;
	strcpy(clean_info[0].filename, "Only Cleanup, Unique String");
	clean_info[0].wait = 1;
	pthread_create(&clean_info[0].tid, NULL, &cleanup_start, &clean_info[0]);

	// start threads
	pub_info[1].wait = 0;
	pub_info[0].wait = 0;
	sub_info[0].wait = 0;
	sub_info[1].wait = 0;
	clean_info[0].wait = 0;

	void *ret = NULL;
	// for both publishers
	pub_num = 0;
	pthread_join(pub_info[pub_num].tid, &ret);
	pub_num++;
	pthread_join(pub_info[pub_num].tid, &ret);
	// for both subscribers
	sub_num = 0;
	pthread_join(sub_info[sub_num].tid, &ret);
	sub_num++;
	pthread_join(sub_info[sub_num].tid, &ret);
	// for cleanup
	pthread_join(clean_info[0].tid, &ret);

	// free
	if(ret != NULL){
		free(ret);
	}
	free(pub_info);
	free(sub_info);

	return 0;
}

