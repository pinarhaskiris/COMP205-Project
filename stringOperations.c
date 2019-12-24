#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "stringOperations.h"

/**
 * Takes a string and how many character which the string has
 * Creates a char** to store all of the words.
 * Assumes all the words can be single character. For this reason it takes number of char of the string.
 * Allocates memory size of number of char times size of char.
 * Then it splits the given string and assigns splitted words into string array
 *
 *
 * @param string a string which has all the words and sentences
 * @param numOfChar number of character in the string
 * @return Returns string array(char **) which contains all the words in the given string seperately
 */
char** parseIntoWords(char * string, int numOfChar){
	char ** words = (char **)malloc(numOfChar*sizeof(char*)); // a pointer of char pointer which stores words

	//Assigning all the index as NULL for safety and later controlling purposes.
	for(int i = 0; i < numOfChar; i++){
		words[i] = NULL;
	}

	char * temp;
	temp = strtok(string," \n\t"); //Splitting
	int index=0; //char pointer array index
	while(temp != NULL){
		if(temp != NULL && temp[0] != 13){ // for avoiding empty words.
			words[index]= temp; // Assigning the splitted word into string array.
		}
		temp = strtok(NULL," \n\t"); //It is about uses of strtok()
		index++; //incrementing index of the words.
	}
	return words;
}



/**
 * Takes a FILE pointer which is points a txt file.
 * Reads the file char by char and increments the value of numOfCh
 * Until it sees EOF
 *
 * @param fp FILE pointer
 * @return return number of char of given file
 */
int numOfChar(FILE * fp){
	int numOfCh =0;
	char chario;

	//Continues until chario is EOF
	while((chario=getc(fp)) != EOF)
		numOfCh++;
	rewind(fp); //back to beginning of the file.
	return numOfCh;
}



/**
 * Calculates number of elements in given string array
 *
 *
 * @param words a string array(char**) which contains words in seperately
 * @return number of words in given string array.
 */
int numOfWords(char ** words){
	int count=0;
	while(words[count] != NULL)
		count++;
	return count;
}


/**
 * change all the characters to lowercase in the given word
 *
 * @param word a word which is wanted to change its characters into their lowercase
 * @return void
 */
void toAllLowercase(char ** word){
	for(int i=0; i< strlen(*word);i++){
		int newLowerChar = tolower((int)(*word)[i]);
		(*word)[i] =(char) newLowerChar;
	}
}



/**
 * Takes a integer and removes chars from the last
 *
 * @param source address of a string which is wanted to trim from the last
 * @param number number of character to trim from the last
 * @return void
 */
void removeCharFromEnd(char ** source, int number){

	//Removes the last character
	char * dest = (char *)malloc(strlen(*source)*sizeof(char));
	int sizeofString = strlen(*source);
	memcpy(dest,*source,sizeofString-number);
	dest[sizeofString-number]='\0';
	*source=dest;
}

/**
 * Takes a string and returns last character of the string
 *
 * @param source string which is wanted to get its last character
 * @return return last character of given string
 */
char showLastChar(char * source){
	return source[(strlen(source)-1)];
}
