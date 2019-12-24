struct Node {
	char * string;	// The word as same as in the given text.
	char * found;	// The word which is found in the internet 
	//struct Node * prev; 
	struct Node * next;	
};
void AddNewNode(struct Node * newnode, struct Node ** source);


