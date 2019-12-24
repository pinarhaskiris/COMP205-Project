#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include "countDifferentWords.h"
#include "Encryption.h"

int main(int argc, char *argv[]) {

printf("These are the functions you can use: ");
printf("1-cryptoSearch\n2-passwordChecker\n3-countDifferent\n4-encrypt\n5-manual\n6-quit\n7-dog\n8-clear\n");
printf("If you don't know what these functions do, you can learn by calling the manual command.\n");

printf(" _       _ _                                   \n");
printf("| |_ ___| | |___                                 \n");
printf("|   | -_| | | . |                                \n");
printf("|_|_|___|_|_|___|                                \n");
printf("\n");
printf(" _ _ _ ___    ___ ___ ___                        \n");
printf("| | | | -_|  | .'|  _| -_|                       \n");
printf("|_____|___|  |__,|_| |___|                       \n");
printf("\n");
printf("                          _                      \n");
printf(" ___ ___ ___    ___ ___ _| |   ___ _ ___ ___ ___ \n");
printf("|  _| .'|   |  | .'|   | . |  | . | |   | .'|  _|\n");
printf("|___|__,|_|_|  |__,|_|_|___|  |  _|_|_|_|__,|_|  \n");
printf("                              |_|                \n");
printf("\n");
printf("                          _                      \n");
printf(" _ _ _ ___    _____ ___ _| |___    ___           \n");
printf("| | | | -_|  |     | .'| . | -_|  | .'|          \n");
printf("|_____|___|  |_|_|_|__,|___|___|  |__,|          \n");
printf("\n");
printf(" _____    _____ _____ _____ _____ __             \n");
printf("|     |  |   __|  |  |   __|   __|  |            \n");
printf("|   --|  |__   |     |   __|   __|  |__          \n");
printf("|_____|  |_____|__|__|_____|_____|_____|         \n");
printf("\n");

	while(1){
		printf("\033[1;34m"); //Set text color
		printf("Can&&Pinar@MEF:");
		printf("\033[0m"); //Reset the text color
		printf("Enter a command 🤘: "); //asking for the user input

		//taking a string to determine which function to operate
		char * input = (char *) malloc(100*sizeof(char));
		gets(input); //taking input(s)

		char *inputs[10]; //a char pointer array to hold the strings
		for(int i = 0; i < 10; i++){ //all of them are null in the beginning, they will be controllec and checked later
			inputs[i] = NULL;
		}


		//SPLITTING THE INPUT
		//Filling the char pointer array as we split the inputs.
		char * temp; //keeping the split piece here for a while
		temp = strtok(input," "); //splitting the first part
		int index=0; //using the char pointer array to hold the indexes
		while(temp != NULL){
			inputs[index]= temp;//filling the char pointer array with split pieces
			temp = strtok(NULL," "); //splitting the next part
			index++;
		}


		int num_of_args =index; // number of arguments

		//NAMES OF THE FUNCTIONS
		char cryptoSearch[]="coin";
		char passwordChecker[] = "passwordChecker";
		char countDifferent[] = "countDifferent";
		char Encryption[] = "encrypt";
		char manual[] = "manual";
		char quit[]="quit";
		char dog[] = "dog";
		char clear[] = "clear";


		//DETERMINING WHICH FUNCTION TO USE
		if(strcmp(inputs[0],quit)==0){ //if the input is quit
			printf("quitting...\n"); //quitting the program
			exit(0);
		}

		else if(strcmp(inputs[0],cryptoSearch)==0){ //calling the cryptoSearch function

			//IDENTIFYING
			char *cmdargs1[] = { "/bin/bash", "./coin.sh", inputs[1], NULL };    //cryptoSearch scenerio1
			char *cmdargs2[] = {"/bin/bash","./coin.sh",inputs[1],inputs[2], NULL };  //cryptoSearch scenerio2

				if(num_of_args==1){  //number of inputs not being enough
					printf("This function needs at least 1 input.\n");

				 }
				else if(num_of_args==2){ //for one input

						if(!fork()) //using fork function to program to run in a image
						  execv(cmdargs1[0], cmdargs1);
						wait(NULL);


				 } else if(num_of_args==3){ //for two inputs
						if(!fork())
						  execv(cmdargs2[0], cmdargs2);
						wait(NULL);

				 }
				 else{ //wrong number of inputs
					 printf("This function can take 1,2 or 3 inputs.\n");

				 }
		}

		else if(strcmp(inputs[0],passwordChecker)==0){ //for passwordChecker function
			char *cmdargs1[] = { "/bin/bash", "./passwordChecker.sh", inputs[1], NULL }; //using the shell function

			if(num_of_args==1){  //in the case of not having enough inputs
			printf("This function needs 1 input.\n");
			   }

			else if(num_of_args==2){ //for 1 input
				if(!fork()) //to run the program in a image
				  execv(cmdargs1[0], cmdargs1);
				wait(NULL);
			 }
			 else{ //wrong nuber of inputs
			 printf("This function needs 1 input.\n");

		   }
		}

		else if(strcmp(inputs[0],clear)==0){ //clear function
			char *cmdargs1[] = { "/bin/bash", "./clearE.sh", inputs[1], NULL }; //using the shell function

		 if(num_of_args==1){ //clear function doesn't take any inputs
				if(!fork()) //to run the program in a image
				  execv(cmdargs1[0], cmdargs1);
				wait(NULL);
			 }
			 else{ //for wrong number of inputs
			 printf("This function does not need any inputs.\n");

		   }
		}

		else if(strcmp(inputs[0],dog)==0){ //dog function
			char *cmdargs1[] = { "/bin/bash", "./catE.sh", inputs[1], NULL }; //using the shell function

			if(num_of_args==1){  //in the case of not having enough inputs
			printf("This function needs 1 input.\n");
				 }

			else if(num_of_args==2){ //correct amount of inputs
				if(!fork()) //to run the program in a image
					execv(cmdargs1[0], cmdargs1);
				wait(NULL);
			 }
			 else{ //for wrong number of inputs
			 printf("This function needs 1 input.\n");

			 }
		}


		else if(strcmp(inputs[0],Encryption)==0){ //for encryption function
			/*if(num_of_args==1 || num_of_args==2){  //in the case of having not enough inputs
			printf("This function needs 2 inputs.\n");
			   }
			else */if(num_of_args==3){ //correct amoount of inputs
				
				if(!fork()) //to run the program in a image
					encryption(inputs[1],inputs[2]); //using the c function
				wait(NULL);
			 }
			 else{ //for wrong number of inputs
			 printf("This function needs 2 inputs.\n");
		   }
		}

		else if(strcmp(inputs[0],countDifferent)==0){ //for countDifferent function
			if(num_of_args==1){  //in the case of not having enough inputs
			printf("This function needs at least 1 input.\n");
			   }
			else if(num_of_args==2){ //correct number of inputs
				if(!fork()) //to run the program in a image
					countDifferentWords(inputs[1]); //using the c function
				wait(NULL);
			 }
			 else{ //for wrong number of inputs
			 printf("This function can take 1 input..\n");
		   }
		}

		else if(strcmp(inputs[0],manual)==0){ //for manual function
			if(num_of_args==1){  //in the case of not having enough inputs
			printf("This function needs 1 input.\n");
				}
			else if(num_of_args==2){ //correct number of inputs

				if(strcmp(inputs[1],cryptoSearch)==0){ //for coin command

					printf("Coin function created by Can\nIt is based on shell script\n\n");
					printf("Gets webadress html file as a txt called as given variable.\n");
					printf("Controls whether there is a page according to variable which is given.\n");
					printf("If there is not, the program will be stop.\n");
					printf("If there is, txt file will be created.\n");
					printf("For the log file creation time is taken.\n");
					printf("\n\nHow To Use\n");
					printf("coin Argument1 ---> Shows coin information\n");
					printf("coin Argument1 Argument2 ---> Compares 2 coin and shows the best\n");
					printf("Arguments must be a coin");

				}
				else if(strcmp(inputs[1],passwordChecker)==0){ //for passwordChecker command

					printf("PasswordChecker function created by Pınar.\nIt is based on shell script.\n\n");
					printf("This command takes an input, checks the input password's strongness according to features such as:\n ");
					printf("- Being at least 8 characters long,\n- Having at least 1 lowercase, 1 uppercase letter,\n");
					printf("- Having at least 1 special character and 1 number.");
					printf("\n\nHow To Use\n: ");
					printf("passwordChecker Argument1 ---> Gives information and suggestions according to the features above.\n");
				}

				else if(strcmp(inputs[1],countDifferent)==0){ //for countDifferent command

					printf("CoundDifferent function created by Can\nIt is based on C\n\n");
					printf("Takes word from the word array.\n");
					printf("Searches the word in the internet.\n");
					printf("If it is not found,it trims the last character. Searches again.\n");
					printf("If it is not again, it continues to trim and search again. \n");
					printf("If there is no char left. The word will be stored in different word array");
					printf("If we have found the word in the internet, there is 1 check left.\n");
					printf("Does the word has a punctuation mark?\n");
					printf("If the word has a punctuation mark,\n");
					printf("trims the last char and searches in the internet again\n");
					printf("If the trimmed word is found in the internet, assigns as a found word.\n");
					printf("Later, calculates hash and puts into hash table \n");
					printf("Then, prints the result\n");
					printf("\n\nHow To Use\n");
					printf("countDifferent Argument1 ---> Finds number of differents words in the given file\n");
					printf("Argument1 must be text file.");


				}

				else if(strcmp(inputs[1],Encryption)==0){ //for encrypt command

					printf("Encryption function created by Pınar.\nIt is based on C.\n\n");
					printf("Takes 2 inputs from the user.\nBoth of the inputs has to be an existing file.\n");
					printf("First input is the file that is going to be encrypted.\nSecond input is the file that the encrypted conent will be written on.\n");
					printf("To encrypt the file, following procedure is followed:\n");
					printf("- Taking the ascii value of each character in the file.\n");
					printf("- Taking the mode 127 of each ascii value.\n");
					printf("- Multiplying every value with the ascii code of the first character in rand.txt.\n");
					printf("- These values are stored into a singly linked list.\n");
					printf("- Every node of the linked list is being multiplied with it's next node until the program reaches the end of the linked list.\n");
					printf("- Finally the content of the linked list is written into the file given by the user as the second input.\n");
					printf("\n\nHow To Use:\n");
					printf("encrypt a.txt b.txt ---> Encrypted version of a.txt is written into b.txt.\n");
				}
				else if(strcmp(inputs[1],clear)==0){ //for clear command
					printf("Clear function is written by Pınar.\nIt is based on shell script.\n");
					printf("Takes 0 inputs from the user.\n");
					printf("Does exactly the same thing with the linux command clear.\n");
					printf("Clears the terminal screen.\n");
					printf("\n\nHow To Use:\n");
					printf("clear ---> Clears the terminal screen.\n");
				}

				else if(strcmp(inputs[1],dog)==0){
					printf("Dog function is written by Pınar.\nIt is based on shell script.\n");
					printf("Takes 1 input from the user and prints the content of it.\n");
					printf("The input has to be an existing file.\n");
					printf("If the file is encrypted, program asks user to enter 1 if the user still wants to see the content of the file.\n");
					printf("\n\nHow To Use\n");
					printf("dog Argument1 ---> Shows the content of the Argument1.\n");
					printf("If Argument1 is encrypted, asks user to enter 1 if the user still wants to see the content of the Argument1.\n");

				}

				else if(strcmp(inputs[1],quit)==0){
					printf("Quit function is written by Can.\nIt is based on shell script.\n");
					printf("Takes 0 inputs. Quits the main program.\n");
					printf("\n\nHow To Use:\n");
					printf("quit ---> The program stops and 'quitting..' is printed on screen.\n");
				}
			}
			 else{ //wrong number of inputs
			 printf("This function needs 1 input.\n");
		   }
		}
		else{

			printf("Command not found.\n");
		}
}

return 0;

}
