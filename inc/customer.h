#pragma once

struct customer {
	char* name;
};

struct customer* createCustomer(char* name);
struct customer* loadCustomer(char* name);
void writeCustomer(struct customer* you);
void freeCustomer(struct customer* freedCustomer);
