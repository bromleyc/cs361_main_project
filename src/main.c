#include <stdio.h>
#include <string.h>
#include "../inc/customer.h"
#include "../inc/employee.h"
#include "../inc/ticket.h"
#include "../inc/tools.h"

int main() {
	while(1){
	printf("\nEnter a number to select an option:\n1 - Enter a new customer\n2 - Enter a new employee\n3 - Enter a ticket\n4 -"
			" View a ticket\n5 - View all tickets\n6 - Delete a ticket\n7 - assign a ticket to a new employee\n"
			"8 - unassign a ticket\n0 - exit the program\n");
	int optionSelMain;
	scanf("%d", &optionSelMain);
	char catchBuffer[2];
	getline(catchBuffer, stdin);
	
	switch (optionSelMain){
		case 1:{
		char ticketCreator[64];
		printf("Enter customer name: ");
		getline(ticketCreator, stdin);
		printf("You are about to enter a new customer with the name: %s.\nDo you wish to continue? (y/n)\n", ticketCreator);
		char confirm[2];
		getline(confirm, stdin);
		if (strcmp(confirm,"y")==0 || strcmp(confirm,"Y")==0){
			struct customer* customer = createCustomer(ticketCreator);
			writeCustomer(customer);
			printf("New customer entered: %s\n", customer->name);
			freeCustomer(customer);
		}
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

		printf("You are about to enter a new employee with the following attributes:\n"
			"Name: %s\nTitle: %s\nManager: %s\n\nDo you wish to continue? (y/n)\n", empName, empTitle, empManager);

		char confirm[2];
		getline(confirm, stdin);
		if (strcmp(confirm,"y")==0 || strcmp(confirm,"Y")==0){
			struct employee* employee = createEmployee(empName, empTitle, empManager);
			writeEmployee(employee);
			printf("New Employee Entered: %s\n", employee->name);
			freeEmployee(employee);
		}
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
		
		printf("Please take a moment to review your entries. Do you want to enter the ticket? (y/n)\n");
		char confirm[2];
		getline(confirm, stdin);
		if (strcmp(confirm, "y") == 0 || strcmp(confirm, "Y") == 0) {
			struct customer* customer = loadCustomer(custName);
			struct ticket* ticket = createTicket(subject, desc, prior, NULL, customer);
			writeTicket(ticket);
			printf("New Ticket Entered: %s\n", ticket->subjectLine);
			freeTicket(ticket);
		}
		break;}

		case 4: {
		printf("Enter ticket subject line: ");
		char sub[1024];
		getline(sub, stdin);
		struct ticket* ticket = loadTicket(sub);
		char in[16];
		strFromPriority(in, ticket->priority);
		printf("Subject: %s Customer: %s Priority: %s\n%s\n", ticket->subjectLine, ticket->customer->name, in, ticket->ticketDesc);
		freeTicket(ticket);
		break;}
		
		case 5: {
		printAllTickets();
		break;}

		case 6: {
		printf("Enter a ticket to delete: ");
		char itemToDel[64];
		getline(itemToDel, stdin);
		printf("*******WARNING********\nDeleteing this ticket is permanent, do not continue unless you are sure you want to permanently delete this ticket! Are you sure you want to delete? (y/n)\n");
		char confirm[2];
		getline(confirm, stdin);
		if (strcmp("y", confirm) == 0 || strcmp("Y", confirm) == 0) {	
			deleteLine(itemToDel, "tickets");
		}

		break;}

		case 7: {
		printf("Enter a ticket to reassign: ");
		char subLine[64];
		getline(subLine, stdin);
		printf("Enter the new technician for this ticket: ");
		char newEmp[64];
		getline(newEmp, stdin);	
		struct ticket* ticket = loadTicket(subLine);
		struct employee* employee = loadEmployee(newEmp);

		assignTicket(ticket, employee);
		freeTicket(ticket);
		freeEmployee(employee);
		break;}

		case 8: {
		printf("Enter a ticket to unassign: ");
		char subLine[64];
		getline(subLine, stdin);
		struct ticket* ticket = loadTicket(subLine);
		assignTicket(ticket, NULL);
		freeTicket(ticket);
		break;}	

		case 9: {
		break;}

		case 0: {
		return 0;}
	}
	}
}
