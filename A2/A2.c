/*
FILE          : A2.c
PROJECT       : SENG1050 - A02 – STACKS AND QUEUES USING LINKED LISTS 
PROGRAMMER    : Vicky Nyangoma Kamanyire
FIRST VERSION : 2026 - 10 - 14
DESCRIPTION:  This program implements a simplified web browser history manager using stacks and queues.   

			  Link to Github repository:
*/

#pragma warning (disable: 4996)

#include <stdio.h>
#include <stdlib.h>

struct StackNode {
	char url[50];
	struct StackNode* next;
};

struct Stack {
	struct StackNode* top;
};

int main(void) {

	return 0;
}