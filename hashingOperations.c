#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include "LinkedListString.h"
#include "hashingOperations.h"


/**
 * Takes hash table, index and two string(char*) 
 * Creates a node and puts the words in the node
 * Tries to put the node in hash tables index
 * If the index is available, it puts
 * If the index is not available, it tries to put the node next index
 * This algorithm uses linear probing
 * 
 * 
 * @param hashTable hash table which is wanted to fill in
 * @param hashIndex index of the hash table which is intended to put
 * @param word the word as same as in the given text
 * @param corrected the word which is found in the internet
 * @param hashTableSize size of hash table
 * @return void
 */ 
void putIntoHashTable(struct Node ** hashTable, int hashIndex, char * word, char * corrected,int hashTableSize){
	struct Node * tempNode =(struct Node *)malloc(sizeof(struct Node));
	tempNode->string = word;
	tempNode->found = corrected;
				
	while(1){
		if(hashTable[hashIndex] != NULL){ //If there is a linked list in the hashTable[hashIndex]
			
			if(strcmp(hashTable[hashIndex]->found, corrected) == 0){ //Checks they are same word or not 
				AddNewNode(tempNode, &(hashTable[hashIndex])); //If they have same found word, add
				break;
			}
			else{
				hashIndex++;	//They don't have same found word. We have to assign different index. Linear Probing
				hashIndex = hashIndex % hashTableSize;
			}		
		}
		else{ //If there is no linked list in the hashTable[hashIndex]
			AddNewNode(tempNode, &(hashTable[hashIndex]));
			break;	
		}	
	}
}

/**
 * Creates a hash table in given size.
 * 
 * @param hashTableSize number of index of hash table
 * @return returns a hashTable
 */ 
struct Node ** createHashTable(int hashTableSize){
		struct Node ** hashTable = (struct Node **)malloc(hashTableSize*sizeof(struct Node));
		
		//Assigning all the index as NULL for safety and later controlling purposes.
		for(int cb = 0; cb<hashTableSize; cb++){
			hashTable[cb]=NULL;
			return hashTable;	
		}
}	

/**
 * Takes a word as a input and calculates the index which will be put in hash table
 * 
 * @param word word which is wanted to calculate its index
 * @param hashTableSize size of hash table
 * @return new index for the hash table
 */ 
int calcHash(char * word, int hashTableSize){
				
	int asciiSum = 0;

	//Adding all ASCII value of chars
	for(int l=0; l<strlen(word); l++)
		asciiSum+=(int)word[l];
		
	int hashIndex = asciiSum %hashTableSize; //Found the hash index
	
	return hashIndex;
}


/**
 * @param hashTable hash table which is wanted to print
 * @param hashTableSize size of hash table
 * @return void
 */ 
void printingHashTable(struct Node ** hashTable, int hashTableSize){
	printf("Unique Words:\n");	
	for(int i=0; i<hashTableSize; i++){
		if(hashTable[i] != NULL){	
			printf("%s ", hashTable[i]->found);
		}
	}
}
