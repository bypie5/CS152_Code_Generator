#ifndef __CODE_GENERATION_H__
#define __CODE_GENERATION_H__

#include "stdlib.h"
#include "stdio.h"

#define MAX_LINE_LEN 254
#define MAX_LINE_COUNT 2048

int lines = 0;
char source[MAX_LINE_COUNT][MAX_LINE_LEN];

char codestr[MAX_LINE_LEN];

void emitCode(char* code) {
	sprintf(source[lines], "%s", code);
	lines++;
}

void printCode() {
	int i;
	for (i = 0; i < lines; i++) {
		printf("%s\n", source[i]);
	}
}

int tempCount = 0;
char* newtemp() {
	char* buff = malloc(sizeof(char)*15);
	sprintf(buff, "__temp__%d", tempCount);
	tempCount++;

	return buff;
}

int labelCount = 0;
char* newlabel() {
	char* buff = malloc(sizeof(char)*15);
	sprintf(buff, "__label__%d", labelCount);
	labelCount++;

	return buff;
}

#endif

