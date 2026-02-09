#include "../inc/customer.h"
#include "../inc/tools.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct customer* createCustomer(char* name) {
	struct customer* newCustomer = malloc(sizeof(struct customer)); //function to free
		//Allocate memory, set name
		newCustomer->name = malloc((strlen(name)+1) * sizeof(char));
		strcpy(newCustomer->name, name);
		return newCustomer;
}

struct customer* loadCustomer(char* name) {
	FILE* customerFile = fopen("./data/customers.csv", "r");
	size_t nameLen = strlen(name)+1;
	int foundFlag = 0;	
	
	while(1){
		char newLine[512];
		getline(newLine, customerFile);

		if (strncmp(newLine, name, nameLen)==0) {
			foundFlag = 1;
			break;
		}
	}

	if (foundFlag == 1){
		struct customer* customer = createCustomer(name);
		return customer;
	}
	else{
		return NULL;
	}
}

void writeCustomer(struct customer* you) {
	FILE* customerFile = fopen("./data/customers.csv", "a");
	fputs(you->name, customerFile);
	fputc('\n', customerFile);
	fclose(customerFile);
}

void freeCustomer(struct customer* freedCustomer) {
	free(freedCustomer->name);
	free(freedCustomer);
}
