#include "../inc/ticket.h"
#include "../inc/employee.h"
#include "../inc/customer.h"
#include "../inc/tools.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

struct ticket* createTicket(
		char* subjectLine, 
		char* ticketDesc,
		enum priority priority,
		struct employee* employee,
		struct customer* customer) {
	struct ticket* newTicket = malloc(sizeof(struct ticket));

	//Allocate memory, set members
	newTicket->subjectLine = malloc((strlen(subjectLine)+1)*sizeof(char));
	strcpy(newTicket->subjectLine, subjectLine);
	
	newTicket->ticketDesc = malloc((strlen(ticketDesc)+1)*sizeof(char));
	strcpy(newTicket->ticketDesc, ticketDesc);

	newTicket->priority = priority;
	newTicket->employee = employee;
	newTicket->customer = customer;
	return newTicket;
}

enum priority priorityFromStr(char* priorStr){
	enum priority prior;
	if (strcmp(priorStr, "Low") == 0) {
		prior = Low;
	} else if (strcmp(priorStr, "Medium")) {
		prior = Medium;
	} else {
		prior = High;
	}
	return prior;
}

void strFromPriority(char* in, enum priority prior){	
	if (prior == Low) {
		strcpy(in, "Low");;
	} else if (prior == Medium) {
		strcpy(in, "Medium");
	} else {
		strcpy(in, "High");
	}
}

struct ticket* loadTicket(char* subjectLine){
	FILE* ticketFile = fopen("./data/tickets.csv", "r");
	size_t subjectLen = strlen(subjectLine);
	int foundFlag = 0;
	char newLine[2048];

	while(1){
		getline(newLine, ticketFile);
		if(strncmp(newLine, subjectLine, subjectLen) == 0){
			foundFlag = 1;
			break;
		}
	}
	if(foundFlag == 1){
		strtok(newLine, ",");
		char* ticketDesc = strtok(NULL, ",");
		char* priorStr = strtok(NULL, ",");
		char* empStr = strtok(NULL, ",");
		char* custStr = strtok(NULL, ",");
		struct ticket* ticket;

		if (strcmp(empStr, "NULL") == 0) {
			ticket = createTicket(subjectLine, ticketDesc, priorityFromStr(priorStr), NULL, loadCustomer(custStr));
			fclose(ticketFile);
			return ticket;
		} else {
			ticket = createTicket(subjectLine, ticketDesc, priorityFromStr(priorStr), loadEmployee(empStr), loadCustomer(custStr));
			fclose(ticketFile);
			return ticket;
		}
	} else{
		fclose(ticketFile);
		return NULL;
		}
}

void writeTicket(struct ticket* ticket) {
	FILE* ticketFile = fopen("./data/tickets.csv", "a");
	fputs(ticket->subjectLine, ticketFile);
	fputc(',', ticketFile);
	fputs(ticket->ticketDesc, ticketFile);
	fputc(',', ticketFile);
	
	char* priorString;

	if (ticket->priority == Low){
		priorString = "Low";
	} 
	else if (ticket->priority == Medium){
		priorString = "Medium"; 
	}
	else{
		priorString = "High";
	}
	fputs(priorString, ticketFile);
	fputc(',', ticketFile);
	if(ticket->employee != NULL){
	fputs(ticket->employee->name, ticketFile);
	} else{
	fputs("NULL", ticketFile);
	}
	fputc(',', ticketFile);
	fputs(ticket->customer->name, ticketFile);
	fputc('\n', ticketFile);
	fclose(ticketFile);
}

void assignTicket(struct ticket* ticket, struct employee* newEmployee) {
	ticket->employee = newEmployee;
	deleteLine(ticket->subjectLine, "tickets");
	writeTicket(ticket);

}

void printAllTickets(){
	FILE* tickets = fopen("./data/tickets.csv", "r");
	char currTicket[2048];

	printf("\nTickets list:\n");

	while (getline(currTicket, tickets) != 1) {
		char* subLine;
		subLine = strtok(currTicket,",");
		
		if (subLine == NULL){
			break;
		}

		struct ticket* ticketToPrint = loadTicket(subLine);
		char priorStr[16];
		strFromPriority(priorStr, ticketToPrint->priority);
		
		char empName[128];

		if (ticketToPrint->employee == NULL) {
			strcpy(empName, "None");
		}

		else{
			strcpy(empName, ticketToPrint->employee->name);
		}
		
		
		printf("Subject: %s - Priority: %s - Assigned to: %s\n", subLine, priorStr, empName);

	}
	fclose(tickets);
}

void freeTicket(struct ticket* ticket) {
	free(ticket->subjectLine);
	free(ticket->ticketDesc);
	free(ticket);
}
