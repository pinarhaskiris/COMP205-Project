#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include "IntLinkedList.h"
#include "Encryption.h"
#include "fileOperations.h"
#include "stringOperations.h"
#include <unistd.h>

/**
@param filename is the file that is going to be encrypted.
*/
void makeList(char * filename, char * filename2){
	FILE *fp = fileOpen(filename);  //opening the file
	int numOfCh = numOfChar(fp); //finding how many characters there are in the file
	char * dest = readFileAsString(fp, numOfCh); //reading the file as a string

	char ** chars = parseIntoChars(dest,numOfCh); //separating the content of the file into characters and storing the characters in an array
	putIntoLinkedListChar(chars,numOfCh); //storing the array into a linked list

	FILE *fp2 = fileOpen(filename2);
	printList(fp2, filename2); //writing the linked list into the file

}

char** parseIntoChars(char * string, int numOfChar){ //parsing the content of the file into characters
	char ** chars = (char **)malloc(numOfChar*sizeof(char*)); //to hold the characters

	for(int i = 0; i < numOfChar; i++){ //they are null in the beginning because we are going to check them later
		chars[i] = NULL;
	}

	char * p2 = string;
	int index =0;
	for(int i=0; i< numOfChar; i++){
		char * str = (char *)malloc(2*sizeof(char)); //destination string will get 2 characters. (since we also want to have the end of string character)
		memcpy(str,p2,sizeof(char)); //getting a character from the string we have (the string from the file) and storing it into the str
		str[1] = '\0'; //putting the end of string character
		p2 = p2 + sizeof(char); //increasing the index of the pointer that points to the string we have by one character so that the next character is at the beginning

		chars[index] = str;	//storing the str that consists of two characters (because of the end of string character) into the index of an array that holds char pointers
		index++;
	}
	return chars;
}


void encryption(char * filename, char * filename2){
	if(access(filename, F_OK ) != -1 && access(filename2, F_OK ) != -1 ) {
		makeList(filename, filename2);
		chmod(filename, S_IRWXU);
		printf("The file is encrypted.\n");
	}
	else {
		printf("At least one of the input files do not exist.\n");
	}
	exit(0);
}
