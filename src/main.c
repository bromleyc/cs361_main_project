#include <stdio.h>
#include "../inc/customer.h"
#include "../inc/employee.h"
#include "../inc/ticket.h"
#include "../inc/tools.h"

int main() {
	printf("Enter a number to select an option:\n1 - Enter a new customer\n2 - Enter a new employee\n3 - Enter a ticket\n4 -"
			" View a ticket\n");
	int optionSelMain;
	scanf("%d", &optionSelMain);
	char catchBuffer[2];
	getline(catchBuffer, stdin);
	
	switch (optionSelMain){
		case 1:{
		char ticketCreator[64];
		printf("Enter customer name: ");
		getline(ticketCreator, stdin);
		struct customer* customer = createCustomer(ticketCreator);
		writeCustomer(customer);
		printf("New customer entered: %s\n", customer->name);
		freeCustomer(customer);
		break;}
		
		case 2:{
		printf("Enter employee name: ");
		char empName[64];
		getline(empName, stdin);
		printf("Enter employee title: ");
		char empTitle[32];
		getline(empTitle, stdin);
		printf("Enter the name of the employee's manager: ");
		char empManager[64];
		getline(empManager, stdin);
		struct employee* employee = createEmployee(empName, empTitle, empManager);
		writeEmployee(employee);
		printf("New Employee Entered: %s\n", employee->name);
		freeEmployee(employee);
		break;}
		
		case 3:{
		printf("Enter subject line: ");
		char subject[128];
		getline(subject, stdin);
		printf("Enter a breief desciption of the problem: ");
		char desc[1024];
		getline(desc, stdin);
		enum priority prior;
		printf("Enter a number between 1 and 3. One is the lowest priority and three is the highest: ");
		int priorityChoice;
		scanf("%d", &priorityChoice);
		if(priorityChoice == 1){
			prior = Low;
		} else if (priorityChoice == 2){
			prior = Medium;
		} else{
			prior = High;
		}
		getline(catchBuffer, stdin);
		printf("Enter customer name: ");
		char custName[64];
		getline(custName, stdin);
		struct customer* customer = loadCustomer(custName);
		struct ticket* ticket = createTicket(subject, desc, prior, NULL, customer);
		writeTicket(ticket);
		printf("New Ticket Entered: %s\n", ticket->subjectLine);
		freeTicket(ticket);
		break;}

		case 4: {
		printf("Enter ticket subject line: ");
		char sub[1024];
		getline(sub, stdin);
		struct ticket* ticket = loadTicket(sub);
		char in[16];
		strFromPriority(in, ticket->priority);
		printf("Subject: %s Customer: %s %s\n%s\n", ticket->subjectLine, ticket->customer->name, in, ticket->ticketDesc);
		}

		case 5: {
			printf("Enter a ticket to delete: ");
			char itemToDel[64];
			getline(itemToDel, stdin);
			deleteLine(itemToDel, "tickets");
			}
	}
	return 0;
}
