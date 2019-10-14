/*
=============================================================================================
Name        : DataTranslation.c
Description : Translate a binary code to meaningful operation according to the lookup table.
Data file	 : lookup_table.txt
First column:  the operation string
Second column: the binary code, in the form of string, i.e., character array
Each binary code is 7-digits
Total operation-code pairs are 28.
=============================================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUMBER_OF_PAIRS 28
#define CODE_LENGTH 7
#define OPERATION_STRING_LENGTH 5
#define FILE_NAME "lookup_table.txt"
void printDataDebug(struct unionizedData* uData);

struct unionizedData
{
	char label[OPERATION_STRING_LENGTH];
	char binaryValue[CODE_LENGTH + 1];
};
int main(void) 
{
	setvbuf(stdout, NULL, _IONBF, 0);
	//create a data struct with two members, one for the binary code, the other for the operation string
	struct unionizedData uData[NUMBER_OF_PAIRS];

	//create a lookup table which is an array of the struct


	//initial the lookup table with the data from the txt file
	FILE *file;
	file = fopen(FILE_NAME, "r");
	//check if the file is found / opened successfully or not
	if (!file) {
		printf("File %s not found. Exiting", FILE_NAME);
		exit(1);
	}
	//Read data in
	char temp[CODE_LENGTH];
	int i = 0;//the iterator to control index of the struct array, i.e., the i-th pair
	while (fscanf(file, "%s", temp) == 1) {
		if (strlen(temp) > 0)
		{
			strcpy(uData[i].label, temp);
			fscanf(file, "%s", temp);
			strcpy(uData[i].binaryValue, temp);
			i++;
		}
		if (feof(file))
			break;
	}

	//print the table to double check
	printDataDebug(uData);



	//ask for binary code string
	puts("Please enter 7-digit binary code string:");
	char userString[CODE_LENGTH];
	scanf("%s", userString);

	//Iterate the lookup table to find the user entered code. Use the strcmp function to compare strings
	//If the code string is found, display the operation string
	//if not, display "Invalid binary code"
	int flag = 0;
	int j = 0;
	for (; j < NUMBER_OF_PAIRS; j++) {
		//compare if the user entered string  is the same as current binary code or not
		//if the same, set the flag to one and break
		if (strcmp(userString, uData[j].binaryValue))
		{
			flag = j;
			break;
		}

	}
	//display result
	if (flag == 0) {
		printf("Invalue binary code.\n");
	}
	else {
		//display the operation string for the user enter binary code string
		printf("Operation string is: %5s given the input of %7s.\n", uData[flag].label, userString);

	}
	return EXIT_SUCCESS;
}


void printDataDebug(struct unionizedData* uData)
{
	for (int i = 0; i < NUMBER_OF_PAIRS; i++)
	{
		printf("%5s %7s\n", uData[i].label, uData[i].binaryValue);
	}
}
