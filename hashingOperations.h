int calcHash(char * word, int hashTableSize);
struct Node ** createHashTable(int hashTableSize);
void printingHashTable(struct Node ** hashTable, int hashTableSize);
void putIntoHashTable(struct Node ** hashTable, int hashIndex, char * word, char * corrected,int hashTableSize);
