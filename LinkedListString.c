#include <stdio.h>
#include <stdlib.h>
#include "LinkedListString.h"

/**
 * Adds the given node in given source node.
 * If there is no node in the source. Adds the newnode as a first node
 * If there is a node in the source. Adds the newnode in the end of the linked list.
 * 
 * @param newnode node which is wanted to add
 * @param source  address of a node which is beginning of the linkedlist.
 * @return void
 */
void AddNewNode(struct Node * newnode, struct Node ** source){	
	struct Node *currentnode;
	currentnode = *source;
	newnode->next=NULL;
	//newnode->prev=NULL;
	if(*source == NULL){
		*source=newnode;
	}
	else{
		while(currentnode->next !=NULL){
			currentnode = currentnode->next;
		}
		currentnode->next=newnode;
		source=&currentnode;
		//newnode->prev=currentnode;
	}
}
