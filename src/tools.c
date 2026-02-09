#include <stdio.h>
#include <stdlib.h>

void getline(char* out, FILE* stream){
	while(1){
		int next;
		next = fgetc(stream);
		if (next == EOF) {
			break;
		}
		*out++ = next;
		if (*(out-1) == '\n') {
			*(out-1) = 0;
			break;
		}
	}
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
