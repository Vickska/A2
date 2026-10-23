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
char* pop(struct Stack* stack);
char* peekS(struct Stack* stack);
struct Stack* InitializeStack(void);
bool isEmptyS(struct Stack* stack);

void enqueue(struct Queue* queue, char* newUrl);
char* dequeue(struct Queue* queue);
char* peekQ(struct Queue* queue);
bool isEmptyQ(struct Queue* queue);
struct Queue* InitializeQueue(void);

void updateHistory(struct Queue* queue, char* url);


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

				//checking if there's urls in the forward stack, and clearing them if there are
				while (!isEmptyS(forwardStack)) {
					pop(forwardStack);
				}

				//pushing the url to the top of the stack
				push(backStack, buffer);

				//enquing the url to the queue
				enqueue(queue, buffer);
			}
			printf("\n");


			break;

		case 2:
			printf("You chose to navigate backward.\n");
			printf("\n");

			// Checking if theres nodes in the backstack and if there's more than one node to traverse
			if (isEmptyS(backStack) || backStack->top->next == NULL) {
				printf("You have no visited pages to go back to.\n");
				printf("\n");

			}
			else {
				// popping the current url and pushing it to the forward stack
				char* topUrl = pop(backStack);
				push(forwardStack, topUrl);

				// storing the last accessed webpage url to update the web history queue
				char* lastAccessedWebpage = peekS(backStack);

				// updating the queue
				updateHistory(queue, lastAccessedWebpage);
			}

			break;

		case 3:
			printf("You chose to navigate forward.\n");
			printf("\n");

			//checking if forwardStack is empty
			if (!isEmptyS(forwardStack)) {
				//// popping the current url and pushing it to the back stack
				char* forwardUrl = pop(forwardStack);
				push(backStack, forwardUrl);

				// moving the current url to the rear of the queue
				updateHistory(queue, forwardUrl);
			}
			else {
				printf("You have no pages to go forward to.\n");
				printf("\n");
			}

			break;

		case 4:
			printf("You chose to display current page.\n");
			printf("\n");

			//Peeking at the current page
			char* currentPage = peekS(backStack);
			printf("Your current page: %s\n", currentPage);

			printf("\n");

			break;

		case 5:
			printf("You chose to view the browsing history log.\n");
			printf("\n");

			//Storing the front node temporarily
			struct QueueNode* tempq = queue->front;

			//Traversing the queue
			while (tempq != NULL) {
				printf("%s\n", tempq->url);
				tempq = tempq->next;
			}
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


//STACK FUNCTIONS

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

// METHOD : peekS()
// DESCRIPTION: 
//      This function returns a node from the top of the stack.
// PARAMETERS:
//     struct Stack* stack: the stack being peeked at
// RETURNS:
//	   char* topUrl: the url of the top node.
char* peekS(struct Stack* stack) {

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


//QUEUE FUNCTIONS

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
	newUrlNode->next = NULL;
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

// METHOD : dequeue()
// DESCRIPTION: 
//      This function removes a node from the queue.
// PARAMETERS:
//     struct Queue* queue: the queue being removed from
// RETURNS:
//	   char* frontUrl: the url of the node being dequeued.
char* dequeue(struct Queue* queue) {

	//Checking if the queue is empty
	if (isEmptyQ(queue) == true) {
		printf("Queue is empty.");
		return NULL;
	}

	// temporarily storing the front node
	struct QueueNode* dequeuedNode = queue->front;

	//Storing the url of the node being dequeued
	static char frontUrl[50];
	strcpy(frontUrl, dequeuedNode->url);

	//Making the next node the front of the queue.
	queue->front = dequeuedNode->next;

	//If the next node is empty, set the rear to null
	if (queue->front == NULL) {
		queue->rear = NULL;
	}

	//Freeing the node being popped
	free(dequeuedNode);

	return frontUrl;
}

// METHOD : peekQ()
// DESCRIPTION: 
//      This function returns a node from the front of the queue.
// PARAMETERS:
//     struct Queue* queue: the queue being peeked at
// RETURNS:
//	   char* frontUrl: the url of the front node.
char* peekQ(struct Queue* queue) {

	//Checking if the queue is empty
	if (isEmptyQ(queue) == true) {
		printf("Queue is empty.");
		return NULL;
	}


	//Storing the url of the front node
	static char frontUrl[50];
	strcpy(frontUrl, queue->front->url);

	return frontUrl;


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


// METHOD : updateHistory()
// DESCRIPTION: 
//      This function moves the nodes in the queue to put the most recently accessed web page at the rear
// PARAMETERS:
//     struct Queue* queue: the web history queue
//	   char* newUrl: the url that has just been accessed
// RETURNS:
//	   None.
void updateHistory(struct Queue* queue, char* url) {

	struct QueueNode* current = queue->front;
	struct QueueNode* prev = NULL;
	char* findNode = url;

	//moving the current url to the rear of the queue
	while (current != NULL) {

		// checking if the current node's url matches the url just accessed
		if (strcmp(current->url, findNode) == 0) {

			// if the queue is empty, the url is placed at the front/rear
			if (isEmptyQ(queue) == true) {
				queue->front = current;
				queue->rear = current;
				break;
			}

			// if the node with the current url is already at the rear, do nothing
			if (current == queue->rear) {
				break;
			}

			// if the previous node isnt empty, replace its next node with the node after the current url's node
			if (prev != NULL) {
				prev->next = current->next;
			}
			// if the current url's node is at the front, then the node after it becomes the front.
			else {
				queue->front = current->next;
			}

			// the current url's node is placed after the current rear node
			queue->rear->next = current;

			// the current url node is placed at the rear
			queue->rear = current;

			// the current url node's next is set to null as it is the rear now
			current->next = NULL;
			break;
		}
		prev = current;
		current = current->next;
	}

}
