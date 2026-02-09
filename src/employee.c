#include "../inc/employee.h"
#include "../inc/tools.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct employee* createEmployee(char* name, char* title, char* managerName) {
	struct employee* newEmployee = malloc(sizeof(struct employee));
	
	//Allocate memory, set members
	newEmployee->name = malloc((strlen(name)+1) * sizeof(char));
	strcpy(newEmployee->name, name);

	newEmployee->title = malloc((strlen(title)+1) * sizeof(char));
	strcpy(newEmployee->title, title);

	newEmployee->managerName = malloc((strlen(managerName)+1)*sizeof(char));
	strcpy(newEmployee->managerName, managerName);

	return newEmployee;
}

struct employee* loadEmployee(char* name) {
	FILE* employeeFile = fopen("./data/employees.csv", "r");
	size_t nameLen = strlen(name);
	int foundFlag = 0;
	char newLine[512];

	while(1){
		getline(newLine, employeeFile);
		if (strncmp(newLine, name, nameLen) == 0){
			foundFlag = 1;
			break;
		}
	}
	if (foundFlag == 1) {
		strtok(newLine, ",");
		char* title = strtok(NULL, ",");
		char* managerName = strtok(NULL, ",");
		
		struct employee* employee = createEmployee(name, title, managerName);
	       	return employee;	
	}
	else{
		return NULL;
	}
}

void writeEmployee(struct employee* employee) {
	FILE* employeeFile = fopen("./data/employees.csv", "a");
	fputs(employee->name, employeeFile);
	fputc(',', employeeFile);
	fputs(employee->title, employeeFile);
	fputc(',', employeeFile);
	fputs(employee->managerName, employeeFile);
	fputc('\n', employeeFile);
}

void freeEmployee(struct employee* employee) {
	free(employee->name);
	free(employee->title);
	free(employee->managerName);
	free(employee);
}
