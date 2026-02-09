#pragma once

struct employee {
	char* name;
	char* title;
	char* managerName;
};

struct employee* createEmployee(char* name, char* title, char* managerName);
struct employee* loadEmployee(char* name);
void writeEmployee(struct employee* employee);
void freeEmployee(struct employee* employee);
