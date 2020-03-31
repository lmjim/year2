#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(){
	char *word = "HeLlOWoRlD";
	int len = strlen(word);
        char *anagram = strdup(word); // This uses malloc within, so will need to be freed
	printf("%s\n", anagram);

	// Make lowercase
        int i=0;
        for(; i<len; i++){
                anagram[i] = (char)tolower(anagram[i]);
        }
	printf("%s\n", anagram);

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
	printf("%s\n", anagram);

	free(anagram);
	return 0;
}
