#include <stdio.h>
#include <stdlib.h>
#include "IntLinkedList.h"
#include <ctype.h>

/**
Creating a struct to make nodes.
*/
struct Node {
	int * string;
	struct Node * prev;
	struct Node * next;
};

//setting the head to null, since there is nothing in the beginning
struct Node * head = NULL;

/**
@param fp : is the file that is going to be encrypted.
*/
void printList(FILE *fp, char * filename2){
	struct Node *currentnode = head; //creating a node to go through the linked list
    while (currentnode != NULL){ //as long as there is a node
		int * pntr = (currentnode->string);

				struct Node *iterator = head; //an iterator to write linked list values into the file
				fp = fopen(filename2, "w+"); //opening the file to write it
				while(iterator != NULL){ //as long as there is a node
					fprintf(fp, "%d", iterator->string); //writing the content of each node into the file
					//going through the linked list
					iterator = iterator->next;
					currentnode = currentnode->next;
				}
    }
}

/**
@param chars : holds the characters that are going to be put into the array.
@param numOfChar : number of characters.
*/
void putIntoLinkedListChar(char ** chars, int numOfChar){
	struct Node *newnode, *curnode;
	curnode = head;
	for(int i=0; i<numOfChar;i++){
		AddNewInt(chars[i]);
	}
}

/**
@param string : is the character that is going to be added into the linked list
PS: Reference File: This file's first character's ascii value is being used to multiply the whole linked list content.
*/
void AddNewInt(char * string){
	struct Node *newnode, *currentnode;
	currentnode = head;

	newnode = (struct Node *)malloc(sizeof(struct Node)); //creates a new node

	int ascii = (int)*string; //translating characters into their ascii values
	//ascii = ascii % 10; //taking the mode of the ascii character
	ascii = ascii % 127;

	FILE *fpRef = fopen("rand.txt", "r+"); // opening reference file
	int ch = getc(fpRef); //getting the first character of the reference file
	ascii = ascii * ch; //multiplying the linked list content
	fclose(fpRef);

	newnode->string = ascii; //updating the content of node

	//setting the next and previous of the newnode null
	newnode->next=NULL;
	newnode->prev=NULL;

	//if the newnode is the first node to be added into the linked list
	if(head==NULL){
		head=newnode;
	}
	//if the newnode is not the first node to be added into the linked list
	else{
		while(currentnode->next !=NULL){
			currentnode = currentnode->next;
		}
		currentnode->next=newnode;
		newnode->prev=currentnode;
	}


	if(newnode->next != NULL){
		newnode->string = (((int)(newnode->string) * (int)(newnode->next->string)) % 97); //multiplying nodes and taking the mode (mode value is a prime number)
	}

}
