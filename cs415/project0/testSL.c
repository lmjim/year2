#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct StringList
{
        struct StringList* Next;
        char *Word;
};

struct StringList *MallocSList(char *word){
        // Create a new string list node
        struct StringList *newSL = (struct StringList*)malloc(sizeof(struct StringList));
        newSL->Next = NULL; //(struct StringList*)malloc(sizeof(struct StringList));
        newSL->Word = strdup(word); // This uses malloc within, so will need to be freed
        return newSL;
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

void PrintSList(FILE *file,struct StringList *node){
        // Format output to a file according to specification
        struct StringList *current = node;
        while(current != NULL){
                fprintf(file, "\t%s\n", current->Word);
                current = current->Next;
        }
        return;
}

void FreeSList(struct StringList **node){
        // Free a string list, including all children
        // node is like head in above function
        struct StringList *current = (*node);
	struct StringList *next = NULL;
	while(current != NULL){
                next = current->Next;
                free(current->Word);
                free(current);
                current = next;
        }
        return;
}

int main(){
	char *hello = "Hello";
	char *big = "Big";
	char *wide = "Wide";
	char *world = "World";
	struct StringList *first = MallocSList(hello);
	struct StringList *second = MallocSList(big);
	struct StringList *third = MallocSList(wide);
	struct StringList *fourth = MallocSList(world);
	AppendSList(&first, second);
	AppendSList(&first, third);
	AppendSList(&first, fourth);
	printf("%d\n", SListCount(first));

	FILE *file = fopen("testSLout.txt", "w");
	PrintSList(file, first);
	fclose(file);

	FreeSList(&first);
	return 0;
}
