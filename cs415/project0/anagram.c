/* Name: Lily Jim
 * DuckID: ljim
 * Assignment: CIS 415 Project 0
 * This is my own work except sorting a word alphabetically.
 * Websites Referenced:
 * https://stackoverflow.com/questions/14768230/malloc-for-struct-and-pointer-in-c
 * https://en.cppreference.com/w/c/experimental/dynamic/strdup
 * http://www.cplusplus.com/reference/cstdio/fprintf/
 * https://www.programiz.com/c-programming/library-function/string.h/strlen
 * https://www.programiz.com/c-programming/library-function/ctype.h/tolower
 * https://www.tutorialspoint.com/learn_c_by_examples/program_to_sort_string_characters_in_c.htm
 * https://www.geeksforgeeks.org/strcmp-in-c-cpp/
 */

#include "anagram.h"

struct StringList *MallocSList(char *word){
	// Create a new string list node
	struct StringList *newSL = (struct StringList*)malloc(sizeof(struct StringList));
	newSL->Next = NULL;
	newSL->Word = strdup(word); // This uses malloc within, so will need to be freed
	return newSL;
}

void AppendSList(struct StringList **head, struct StringList *node){
	// Append a string list node to the end/tail of a string list
	struct StringList *current = (*head);
	struct StringList *next = current->Next;
	while(next != NULL){
		current = next;
		next = current->Next;
	}
	current->Next = node;
	return;
}

void FreeSList(struct StringList **node){
	// Free a string list, including all children
	// node is like head in above function
	struct StringList *current = (*node);
	struct StringList *next = NULL;
	while(current != NULL){
		next = current->Next;
		current->Next = NULL;
		int i = 0;
		int len = strlen(current->Word);
		for(; i < len; i++){
			current->Word[i] = 0;
		}
		free(current->Word);
		current->Word = NULL;
		free(current);
		current = next;
	}
	return;
}

void PrintSList(FILE *file,struct StringList *node){
	// Format output to a file according to specification
	struct StringList *current = node;
	while(current != NULL){
		fprintf(file, "\t%s\n", current->Word);
		current = current->Next;
	}
	return;
}

int SListCount(struct StringList *node){
	// Return the number of string in the string list
	int count = 1;
	struct StringList *next = node->Next;
	while(next != NULL){
		count++;
		next = next->Next;
	}
	return count;
}

struct AnagramList* MallocAList(char *word){
	// Create a new anagram node, including the string list node with the word
	struct AnagramList *newAL = (struct AnagramList*)malloc(sizeof(struct AnagramList));
	newAL->Words = NULL;
	newAL->Next = NULL;
	newAL->Anagram = strdup(word); // This uses malloc within, so will need to be freed
	return newAL;
}

void FreeAList(struct AnagramList **node){
	// Free an anagram list, including anagram children and string list words
	struct AnagramList *current = (*node);
	struct AnagramList *next = NULL;
	while(current != NULL){
		next = current->Next;
		current->Next = NULL;
		FreeSList(&current->Words);
		current->Words = NULL;
		int i = 0;
		int len = strlen(current->Anagram);
		for(; i<len; i++){
			current->Anagram[i] = 0;
		}
		free(current->Anagram);
		current->Anagram = NULL;
		free(current);
		current = next;
	}
	return;
}

void PrintAList(FILE *file,struct AnagramList *node){
	// Format output to a file, print anagram list with words, according to spec
	struct AnagramList *current = node;
	while(current != NULL){
		int count = SListCount(current->Words);
		if(count > 1){
			fprintf(file, "%s:%d\n", current->Anagram, count);
			PrintSList(file, current->Words);
		}
		current = current->Next;
	}
	return;
}

void AddWordAList(struct AnagramList **node, char *word){
	// Add a new word to the anagram list
	int len = strlen(word);
	char *anagram = strdup(word); // This uses malloc within, so will need to be freed
	int i=0;
	for(; i<len; i++){
		anagram[i] = (char)tolower(anagram[i]); // Make lowercase
	}
	// Order alphabetically, code modified from tutorialspoint.com
	char temp;
	i=0;
	for(; i<len; i++){
		int j = i+1;
		for(; j<len; j++){
			if(anagram[i] > anagram[j]){
				temp = anagram[i];
				anagram[i] = anagram[j];
				anagram[j] = temp;
			}
		}
	}

	if((*node) == NULL){
		// No anagrams exist, add anagram
		(*node) = MallocAList(anagram);
		(*node)->Words = MallocSList(word);
	}
	else{
		// Check if anagram already exists
		struct AnagramList *current = (*node);
		struct AnagramList *next = current->Next;
		int found = strcmp(current->Anagram, anagram);
		while(next != NULL && found != 0){
			current = next;
			next = current->Next;
			found = strcmp(current->Anagram, anagram);
		}
		if(found == 0){
			// Anagram exists already, append word to StringList
			struct StringList *newSL = MallocSList(word);
			AppendSList(&current->Words, newSL);
		}
		else{
			// Anagram does not exist, add anagram
			current->Next = MallocAList(anagram);
			struct AnagramList *newAL = current->Next;
			newAL->Words = MallocSList(word);
		}
	}

	free(anagram);
	return;
}
