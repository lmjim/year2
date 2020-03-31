/* Name: Lily Jim
 * DuckID: ljim
 * Assignment: CIS 415 Project 0
 * This is my own work except that Roscoe provided pseudo-code for opening files in lab.
 * Websites Referenced:
 * http://man7.org/linux/man-pages/man3/getline.3.html
 * https://stackoverflow.com/questions/13000047/function-to-remove-newline-has-no-effect
 */

#include "anagram.h"

int main(int argc, char **argv){
	FILE *in = stdin;
	FILE *out = stdout;
	if(argc > 3){
		exit(1);
	}
	if(argc > 1){
		in = fopen(argv[1], "r");
	}
	if(argc > 2){
		out = fopen(argv[2], "w");
	}
	if(in == NULL || out == NULL){
		printf("Error: file issue\n");
		if(in == NULL){
			printf("In file issue\n");
			if(out == NULL){
				printf("Out file issue\n");
			}
			else{
				fclose(out);
			}
		}
		else{
			printf("Out file issue\n");
			fclose(in);
		}
		exit(1);
	}

	struct AnagramList *list = NULL;
	char *word = NULL; // getline will allocate memory, will need to be freed
	size_t len = 0;
	ssize_t chars;
	while((chars = getline(&word, &len, in)) != -1){
		// Remove newline character from word
		if(word[chars - 1] == '\n'){
			word[chars - 1] = '\0';
		}
		// Add word to list of anagrams
		AddWordAList(&list, word);
	}
	PrintAList(out, list);

	free(word);
	FreeAList(&list);
	fclose(in);
	fclose(out);
	return 0;
}
