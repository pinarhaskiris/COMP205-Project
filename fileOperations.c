#include <stdio.h>
#include <stdlib.h>
#include "fileOperations.h"


/**
 * Takes filename as a input and opens the file
 * @param filename a string file name
 * @return FILE pointer of the file. 
 */ 
FILE * fileOpen(char * filename){
	
	FILE *fp;
	fp = fopen(filename, "r");
	if(fp == NULL) {
		perror("Please try another file in the directory");
		exit(0);
	}
	return fp;
}


/**
 * Take FILE pointer as a input and closes the file 
 * @param fp FILE pointer
 * @return void
 */
void fileClose(FILE * fp){
	fclose(fp);
}

/**
 * Reads the file char by char and writes into a char* char by char
 * Until it sees EOF 
 * 
 * @param fp FILE pointer
 * @param numOfCh number of char in the file
 * @return all the data as a string
 */ 
char * readFileAsString(FILE * fp, int numOfCh){
	char chario;	
	char * dest = (char *)malloc(numOfCh*sizeof(char)); // String(char*) target
	char * index = dest; // Target index
	
	//Continues until chario is EOF
	while((chario=getc(fp)) != EOF){
		*index = chario;
		index++;	
	}
	fileClose(fp);
	return dest;
}
