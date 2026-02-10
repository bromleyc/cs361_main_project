#pragma once
#include <time.h>

enum priority {Low, Medium, High};

struct ticket {
	time_t ceatedDateTime;
	time_t closedDateTime;
	char* subjectLine;
	char* ticketDesc;
	enum priority priority;
	struct employee* employee;
	struct customer* customer;
};

struct ticket* createTicket(
		char* subjectLine, 
		char* ticketDesc, 
		enum priority priority, 
		struct employee*, 
		struct customer*);

enum priority priorityFromStr(char* priorStr);
void strFromPriority(char* in, enum priority prior);
struct ticket* loadTicket(char* subjectLine);
void writeTicket(struct ticket*);
void freeTicket(struct ticket*);
