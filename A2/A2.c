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
#include <string.h>

struct StackNode {
	char url[50];
	struct StackNode* next;
};

struct Stack {
	struct StackNode* top;
};


// Function prototypes
void push(struct Stack* stack, char* newUrl);
struct Stack* InitializeStack(void);

int main(void) {

	bool exit = false;

	struct Stack* stacklist = InitializeStack();

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

		//Allowing the user to add a new url to the top of the stack
		case 1:
			printf("You chose to visit a new web page.\n");
			printf("\n");

			// Creating buffer to receive input
			char buffer[50];

			// Asking the user for the url
			printf("Enter webpage url: ");
			scanf("%49s", buffer);

			// Stop getting input if the user enters an invalid url
			if (strcmp(buffer, "") == 0) {
				printf("Please enter a valid url.\n");
				break;
			}
			else {
				push(stacklist, buffer);
			}
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

// METHOD : push()
// DESCRIPTION: 
//      This function adds a new node to the stack.
// PARAMETERS:
//     struct Stack* stack: the stack being added to
//	   char* newUrl: the url being added to the stack
// RETURNS:
//	   None.
void push(struct Stack* stack, char* newUrl) {

	// Creating a new node for the new url
	struct StackNode* newUrlNode = malloc(sizeof(struct StackNode));

	if (newUrlNode == NULL)
	{
		printf("Could not allocate memory.\n");
		return;
	}

	// Adding the url to the new node
	strcpy(newUrlNode->url, newUrl);

	//linking the previous node
	newUrlNode->next = stack->top;

	// Adding the new node to the top of the stack
	stack->top = newUrlNode;
}


// METHOD : InitializeStack()
// DESCRIPTION: 
//      This function allocates memory to initialize a stack.
// PARAMETERS:
//      None.
// RETURNS:
//		struct Stack* stack : A stack struct.
struct Stack* InitializeStack(void) {
	struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));

	if (stack == NULL) {
		printf("Could not allocate memory.");
	}
	stack->top = NULL;
	return stack;
}

