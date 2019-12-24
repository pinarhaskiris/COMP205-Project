#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include "hashingOperations.h"
#include "countDifferentWords.h"
#include "fileOperations.h"
#include "stringOperations.h"



/**
 * Calculates how many different words file has.
 * 
 * @param filename a file name which is wanted to open
 * @return void
 */ 
void countDifferentWords(char * filename){
	int hashTableSize = 10000;
	FILE * fp = fileOpen(filename); 							    //opens file
	int numOfCh = numOfChar(fp); 									//how many character does file has
	char * dest = readFileAsString(fp, numOfCh); 					//Reads a file as a string
	char ** words = parseIntoWords(dest,numOfCh); 					//parse into words
	struct Node ** hashTable = createHashTable(hashTableSize);		//creating hash table
	checkWord(words,hashTable,hashTableSize);						//checks every word and prints the results
	exit(0);
}


/**
 * 
 * Takes word from the word array.
 * Searches the word in the internet.
 * If it is not found,it trims the last character. Searches again.
 * If it is not again, it continues to trim and search again. 
 * If there is no char left. The word will be stored in different word array
 * If we have found the word in the internet, there is 1 check left.
 * Does the word has a punctuation mark?
 * If the word has a punctuation mark, trims the last char and searches in the internet again
 * If the trimmed word is found in the internet, assigns as a found word.
 * Later, calculates hash and puts into hash table 
 * Then, prints the result
 * 
 * 
 * @param words a string array which stores words seperately
 * @param hashTable a hash table which is string linked list array
 * @param hashTableSize number of linked lists in the hash table
 * @return void
 */ 
void checkWord(char ** words, struct Node ** hashTable, int hashTableSize){	
	printf("***********************************************************************************************\n");
	
	
	FILE * fp2;
	int notFoundsIndex = 0;
	int num_of_words = numOfWords(words);
	char ** notFounds = (char **)malloc(num_of_words*sizeof(char*)); //In the worst case, not all words are found
	
	//Assigning all the index as NULL for safety and later controlling purposes.
	for(int i = 0; i < num_of_words; i++){ 
		notFounds[i] = NULL;
	}
	
	char * dest; //Stores form of the word which is found in the internet
	for(int i=0; words[i] != NULL; i++ ){
		char * word = words[i]; //Everytime we will check one of the word from the string array.
		dest = word;
		toAllLowercase(&word); //Before searching in the internet change every char to lowercase
		callScript(word); //Call the script, searching in the internet
		
		//Did we find the word in the internet?
		fp2 = fileOpen("isthere.txt"); 
		char isThere = getc(fp2);
		fileClose(fp2);
		
		//If we didn't find the word in the internet.
		for(int j = 1; isThere != '0'; j++){
			
			//special case for the dictionary website
			char ch1 = showLastChar(dest); 
			if(ch1 == 13){ //for avoiding only removing not seen character.
				removeCharFromEnd(&dest,1);
				ch1 = showLastChar(dest);
			}
			if(ch1 == 58){
				isThere = 1;
			}	
			
			//If the all word is not in the internet
			if(isThere == '2'){
				notFounds[notFoundsIndex] = words[i]; //the all word is not in the internet. Stores in the notFounds
				notFoundsIndex++; //Found 1 more not found word
				break;
			}
			removeCharFromEnd(&dest,j); 	//Every for loop we trim the last character
			callScript(dest); 					//Then search again
			fp2 = fileOpen("isthere.txt"); 		//
			isThere = getc(fp2); 				//And checks.
			fileClose(fp2);
		}
		
		//If we come here, we have found the word or all the word is not in the internet
		// isThere --> 0 or 2
		
		
		//Found the word in the internet. Let's put into hashTable	
		if(isThere == '0'){	
			char * temp = dest;
			char c = showLastChar(dest);
			
			//Last check before putting into hashTable. Does word have punctuation marks?
			int b1 =checkPuncMarks(33, 47, &temp); // checks Ascii Table 33-47
			int b2 =checkPuncMarks(58, 64, &temp); // checks Ascii Table 58-64
			int b3 =checkPuncMarks(91, 96, &temp); // checks Ascii Table 91-96
			int b4 =checkPuncMarks(123, 126, &temp); // checks Ascii Table 123-126
			
			int val = atoi(dest);
			
			if(val!=0){ //if dest is a number
				//controlling original word has a punctuation mark
				checkPuncMarks(33, 47, &word); // checks Ascii Table 33-47
				checkPuncMarks(58, 64, &word); // checks Ascii Table 58-64
				checkPuncMarks(91, 96, &word); // checks Ascii Table 91-96
				checkPuncMarks(123, 126, &word); // checks Ascii Table 123-126
				
				int val2=atoi(word);
				if(val2!=0){ // if word is a number too
					int hashIndex = calcHash(word,hashTableSize);			 		//Calculate hash
					putIntoHashTable(hashTable,hashIndex,word,word,hashTableSize);		
				}
				else{
					int hashIndex = calcHash(temp,hashTableSize);			 		//Calculate hash
					putIntoHashTable(hashTable,hashIndex,word,temp,hashTableSize);
				}
			}
			else{
				if(b1 || b2 || b3 || b4){ //if removed punctuation mark recheck the word
					callScript(temp); 					//Call the script, searching in the internet
					//Did we find the word in the internet?
					fp2 = fileOpen("isthere.txt"); 
					isThere = getc(fp2);
					fileClose(fp2);
					
					if(isThere == '0'){	 //If the word is in the internet after removing punctuation mark
						int hashIndex = calcHash(temp,hashTableSize);			 		//Calculate hash
						putIntoHashTable(hashTable,hashIndex,word,temp,hashTableSize);	//the all word is not in the internet	
					}
				}
				else{
					int hashIndex = calcHash(dest,hashTableSize);			 		//Calculate hash
					putIntoHashTable(hashTable,hashIndex,word,dest,hashTableSize);	//the all word is not in the internet
				}			
			}
		}//inner for done	
	}
	//print all the results
	printResult(hashTable,hashTableSize, notFounds,words);
}

/**
 * 
 * Prints all the results.
 * 
 * @param hashTable a hash table which is string linked list array
 * @param hashTableSize number of linked lists in the hash table
 * @param notFounds a string linked list array which store words which is not found in the internet
 * @param words a string array which stores words seperately
 * @return void
 */ 			
void printResult(struct Node ** hashTable, int hashTableSize, char ** notFounds, char ** words ){
	
	int num_of_words = numOfWords(words);
	
	printf("***********************************************************************************************\n");
	printf("Number of words: %d\n",num_of_words);
	
	
	int countOfDifferent = 0;
	for(int i=0; i<hashTableSize; i++){
		if(hashTable[i] != NULL){
			countOfDifferent++;
		}
	}
	printf("Number of different words: %d\n", countOfDifferent);
	
	int countOfNotFounds =0;
	for(int i=0; notFounds[i] != NULL; i++){
		countOfNotFounds++;
		
	}
	printf("Number of words which are not found: %d\n",countOfNotFounds);
	
	if(countOfNotFounds != 0){
		printf("These words are: \n");
		for(int i=0; notFounds[i] != NULL; i++){
			printf("%s\n",notFounds[i]);
		}
	}
	
	//Prints all the words which is found
	printingHashTable(hashTable,hashTableSize);
	printf("\a\n");
	
}


/**
 * Checks whether word has a punctuation marks or not.
 * 
 * 
 * @param lowBound ascii low bound
 * @param highBound ascii high bound
 * @param dest word which is wanted to check
 * @return int if word has a punctuation mark returns 1.
 */
int checkPuncMarks(int lowBound, int highBound, char ** dest){		
	//FILE * fp2;
	char c = showLastChar(*dest);	
	if(c == 13){ //for avoiding only removing not seen character.
		removeCharFromEnd(dest,1);
		c = showLastChar(*dest);
	}
	for(int i =lowBound; i<=highBound; i++){ 
		if(c == i){ //Word has punctuation mark
			removeCharFromEnd(dest,1); 	//We trim the last character
			return 1;	
		}
	}
	return 0;
}	


/**
 * Takes a string to send to the script
 * 
 * @param word a string to send to the string
 * @return void
 */
void callScript(char * word){

	char *cmdargs[] = { "/bin/bash", "./isThereaWord.sh", word , NULL }; //isThereaWord 

	//Calls bash script
	if(!fork())
		execv(cmdargs[0], cmdargs);
	wait(NULL);
}


