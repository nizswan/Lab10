//Cristian McGee Cop3502C Lab Assignment 10
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Trie structure
struct Trie
{
    struct Trie *nextTrees[26];
    int count;
};
struct Trie *createTrie();
// Inserts the word to the trie structure
void insert(struct Trie *pTrie, char *word)
{
    struct Trie *temp = pTrie;
    for(int i = 0; i < strlen(word); i++){
        int index = word[i] - 'a';
        if(temp->nextTrees[index] == NULL){
            temp->nextTrees[index] = createTrie();
        }
        temp = temp->nextTrees[index];
    }
    temp->count += 1;
    //printf("%s has been inserted and has a count of %d\n", word, temp->count);
    
}

// computes the number of occurances of the word
int numberOfOccurances(struct Trie *pTrie, char *word)
{
    struct Trie *temp = pTrie;
    for(int i = 0; i < strlen(word); i++){
        int index = word[i] - 'a';
        if(temp->nextTrees[index] == NULL){
            return 0;
        }
        temp = temp->nextTrees[index];
    }
    return temp->count;
}

// deallocate the trie structure
void *deallocateTrie(struct Trie *pTrie)
{
    if(pTrie == NULL){
        return NULL;
    }
    for(int i = 0; i < 26; i++){
        deallocateTrie(pTrie->nextTrees[i]);
    }
    free(pTrie);
    return NULL;
}

// Initializes a trie structure
struct Trie *createTrie()
{
    struct Trie* tempTree = (struct Trie*) malloc(sizeof(struct Trie));
    for(int i = 0; i < 26; i++){
        tempTree->nextTrees[i] = NULL;
    }
    tempTree->count = 0;
    return tempTree;
}

// this function will return number of words in the dictionary,
// and read all the words in the dictionary to the structure words
int readDictionary(char *filename, char **pInWords)
{
    FILE *fp = fopen(filename, "r");
    int n;
    fscanf(fp, "%d", &n);
    for(int i = 0; i < n; i++){
        fscanf(fp, "%s", pInWords[i]);
    }
    fclose(fp);
    return n;
}

int main(void)
{
	char *inWords[256];
	for (int i = 0; i < 256; i++) {
        inWords[i] = malloc(100 * sizeof(char));
    }
	//read the number of the words in the dictionary
	int numWords = readDictionary("dictionary.txt", inWords);
	for (int i=0;i<numWords;++i)
	{
		printf("%s\n",inWords[i]);
	}
	
	struct Trie *pTrie = createTrie();
	for (int i=0;i<numWords;i++)
	{
		insert(pTrie, inWords[i]);
	}
	// parse lineby line, and insert each word to the trie data structure
	char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
	for (int i=0;i<5;i++)
	{
		printf("\t%s : %d\n", pWords[i], numberOfOccurances(pTrie, pWords[i]));
	}
	pTrie = deallocateTrie(pTrie);
	if (pTrie != NULL)
		printf("There is an error in this program\n");
	return 0;
}