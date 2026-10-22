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

struct QueueNode {
	char url[50];
	struct QueueNode* next;
};

struct Queue {
	struct QueueNode* front;
	struct QueueNode* rear;

};

// Function prototypes
void push(struct Stack* stack, char* newUrl);
struct Stack* InitializeStack(void);
bool isEmptyS(struct Stack* stack);
char* pop(struct Stack* stack);
char* peek(struct Stack* stack);

void enqueue(struct Queue* queue, char* newUrl);
bool isEmptyQ(struct Queue* queue);
struct Queue* InitializeQueue(void);





int main(void) {

	bool exit = false;

	struct Stack* backStack = InitializeStack();
	struct Stack* forwardStack = InitializeStack();
	struct Queue* queue = InitializeQueue();

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
				//pushing the url to the top of the stack
				push(backStack, buffer);

				//enquing the url to the queue
				enqueue(queue, buffer);
			}

			break;

		case 2:
			printf("You chose to navigate backward.\n");
			printf("\n");

			char* topUrl = pop(backStack);
			push(forwardStack, topUrl);

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

// METHOD : pop()
// DESCRIPTION: 
//      This function removes a node from the top of the stack and returns its url.
// PARAMETERS:
//     struct Stack* stack: the stack being removed from
//	   char* newUrl: the url being removed from the stack
// RETURNS:
//	   char* topUrl: the url of the node being popped.
char* pop(struct Stack* stack) {

	//Checking if the stack is empty
	if (isEmptyS(stack) == true) {
		printf("Stack is empty.");
		return NULL;
	}

	// temporarily storing the top node
	struct StackNode* poppedNode = stack->top;

	//Storing the url of the node being popped
	static char topUrl[50];
	strcpy(topUrl, poppedNode->url);

	//Making the next node the top of the stack.
	stack->top = poppedNode->next;

	//Freeing the node being popped
	free(poppedNode);

	return topUrl;

	
}

// METHOD : peek()
// DESCRIPTION: 
//      This function returns a node from the top of the stack.
// PARAMETERS:
//     struct Stack* stack: the stack being peeked at
//	   char* newUrl: the url being from the top of the stack
// RETURNS:
//	   char* topUrl: the url of the top node.
char* peek(struct Stack* stack) {

	//Checking if the stack is empty
	if (isEmptyS(stack) == true) {
		printf("Stack is empty.");
		return NULL;
	}


	//Storing the url of the top node
	static char topUrl[50];
	strcpy(topUrl, stack->top->url);

	return topUrl;


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

// METHOD : isEmptyS()
// DESCRIPTION: 
//      This function checks if the stack is empty
// PARAMETERS:
//	    struct Stack* stack : A stack struct.
// RETURNS:
//      bool isEmpty: a boolean variable that checks if the stack is empty or not.
bool isEmptyS(struct Stack* stack) {

	// Checking if the top of the stack is empty
	bool isEmpty = stack->top == NULL;
	return isEmpty;
}


// METHOD : enqueue()
// DESCRIPTION: 
//      This function adds a new node to the queue.
// PARAMETERS:
//     struct Queue* queue: the queue being added to
//	   char* newUrl: the url being added to the queue
// RETURNS:
//	   None.
void enqueue(struct Queue* queue, char* newUrl) {

	// Creating a new node for the new url
	struct QueueNode* newUrlNode = malloc(sizeof(struct QueueNode));

	if (newUrlNode == NULL)
	{
		printf("Could not allocate memory.\n");
		return;
	}

	// Adding the url to the new node
	strcpy(newUrlNode->url, newUrl);

	//Setting new node as the first and last node if the queue is empty
	if (isEmptyQ(queue) == true) {
		queue->front = newUrlNode;
		queue->rear = newUrlNode;
		return;
	}
	//Placing new node at the back if the queue is not empty
	queue->rear->next = newUrlNode;
	queue->rear = newUrlNode;
}

// METHOD : InitializeQueue()
// DESCRIPTION: 
//      This function allocates memory to initialize a queue.
// PARAMETERS:
//      None.
// RETURNS:
//		struct Queue* queue : A queue struct.
struct Queue* InitializeQueue(void) {
	struct Queue* queue = (struct Queue*)malloc(sizeof(struct Queue));

	if (queue == NULL) {
		printf("Could not allocate memory.");
	}
	queue->front = NULL;
	queue->rear = NULL;

	return queue;
}

// METHOD : isEmptyQ()
// DESCRIPTION: 
//      This function checks if the queue is empty
// PARAMETERS:
//		struct Queue* queue : A queue struct.
// RETURNS:
//      bool isEmpty: a boolean variable that checks if the queue is empty or not.
bool isEmptyQ(struct Queue* queue) {

	// Checking if the top of the stack is empty
	bool isEmpty = queue->front == NULL;
	return isEmpty;
}
