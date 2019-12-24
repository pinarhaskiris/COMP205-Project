can = countDifferentWords.o LinkedListString.o fileOperations.o hashingOperations.o stringOperations.o
pinar = Encryption.o IntLinkedList.o

ready : $(can) $(pinar) main.o
	gcc -w -o ready $(can) $(pinar) main.o

main.o : main.c countDifferentWords.h
	cc  -w -c main.c

countDifferentWords.o : countDifferentWords.c countDifferentWords.h fileOperations.h hashingOperations.h stringOperations.h
	cc  -w -c countDifferentWords.c

LinkedListString.o : LinkedListString.c LinkedListString.h
	cc  -w -c LinkedListString.c

fileOperations.o : fileOperations.c fileOperations.h
	cc  -w -c fileOperations.c

hashingOperations.o : hashingOperations.c hashingOperations.h LinkedListString.h
	cc  -w -c hashingOperations.c

stringOperations.o : stringOperations.c stringOperations.h
	cc  -w -c stringOperations.c

Encryption.o : Encryption.c Encryption.h
	cc  -w -c Encryption.c

IntLinkedList.o : IntLinkedList.c IntLinkedList.h
	cc  -w -c IntLinkedList.c

clear:
	rm -f $(can) $(pinar) main.o
