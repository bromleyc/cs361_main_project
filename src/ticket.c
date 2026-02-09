#include "../inc/ticket.h"
#include "../inc/employee.h"
#include "../inc/customer.h"
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
}

void freeTicket(struct ticket* ticket) {
	free(ticket->subjectLine);
	free(ticket->ticketDesc);
	free(ticket);
}
