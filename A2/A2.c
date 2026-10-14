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
#include <stdbool.h>

struct StackNode {
	char url[50];
	struct StackNode* next;
};

struct Stack {
	struct StackNode* top;
};



int main(void) {

	bool exit = false;

	printf("Web Browser History Manager\n");
	printf("\n");

	while (exit == false) {
		printf("Menu\n");
		printf("1. Visit New Web Page\n");
		printf("2. Navigate Backward\n");
		printf("3. Navigate Forward\n");
		printf("4. Display Current Page\n");
		printf("5. Browsing History Log\n");
		printf("6. Exit\n");
		printf("Select an operation: \n");

		int choice;
		scanf("%d", &choice);

		switch (choice) {
		case 1:
			printf("You chose to visit a new web page.\n");
			printf("\n");
			break;

		case 2:
			printf("You chose to navigate backward.\n");
			printf("\n");
			break;

		case 3:
			printf("You chose to navigate forward.\n");
			printf("\n");
			break;

		case 4:
			printf("You chose to display current page.\n");
			printf("\n");
			break;

		case 5:
			printf("You chose to view the browsing history log.\n");
			printf("\n");
			break;

		case 6:
			printf("You chose to exit.\n");
			printf("\n");
			exit = true;
			break;
		
		default:
			printf("Invalid choice. Please try again.\n");
			printf("\n");
			break;
		}

	}
	return 0;
}
