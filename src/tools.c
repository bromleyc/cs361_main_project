#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int getline(char* out, FILE* stream){
	while(1){
		int next;
		next = fgetc(stream);
		if (next == EOF) {
			return 1;
		}
		*out++ = next;
		if (*(out-1) == '\n') {
			*(out-1) = 0;
			return 0;
		}
	}
}

void deleteLine(char* itemToDel, char* table) {
	char filePath[64];
	strcpy(filePath, "./data/");
	strcat(filePath, table);
	strcat(filePath, ".csv");
	strcat(itemToDel, ",");
	FILE* file = fopen(filePath, "r");
	FILE* newFile = fopen("./data/temp", "w");
	int itemLen = strlen(itemToDel);
	while (1) {
		int eofFlag = 0;
		char nextLine[2048];
		eofFlag = getline(nextLine, file);
		
		if(eofFlag == 1){
			break;
		}	
		if (strncmp(itemToDel, nextLine,itemLen)!=0) {
			strcat(nextLine, "\n");
			fputs(nextLine, newFile);
		}
	}
	fclose(file);
	fclose(newFile);
	remove(filePath);
	rename("./data/temp", filePath);

	return;
}

void nextline(FILE* stream){
	while(1){
		int c;
		c = fgetc(stream);
		if (c == '\n' || c == EOF) {
		break;
		} 
	}
}
