#include <stdio.h>
#include <stdlib.h>
#include "deq.h"

/* A function (and global) that can trigger malloc fails on demand. */
int mallocFail = 0;
void* myMalloc(size_t size) {
	if (mallocFail) { return NULL; }
	else { return malloc(size); }
}

int main()
{
	// store result of calling functions
	int result;

	// a variable to store data popped from the queue
	int data;

	// a pointer to a double-ended queue
	DEQueue *qPtr = NULL;

	// initialise the queue - passing the address of our
	// queue pointer as an input so it can be modified 
	// to point to the memory allocated for the queue
	result = initDEQueue(&qPtr);
	if (result != SUCCESS)
	{
		printf("An error occurred when attempting to initialise the queue\n");
	}
	else
	{
		printf("Queue initialised successfully\n");
	}

	// try popping the head of the queue - this should fail since the
	// queue is empty
	result = popHead(qPtr, &data);
	if (result != POP_EMPTY_DEQ)
	{
		printf("Error: should have detected attempt to pop from an empty queue\n");
	}
	else
	{
		printf("Correctly identified attempt to pop from an empty queue\n");
	}

	// try peeking at the head of the queue - this should fail since the
	// queue is empty
	result = peekHead(qPtr, &data);
	if (result != PEEK_EMPTY_DEQ)
	{
		printf("Error: should have detected attempt to peek at the head of an empty queue\n");
	}
	else
	{
		printf("Correctly identified attempt to peek at the head of an empty queue\n");
	}

	// try peeking at the tail of the queue - this should fail since the
	// queue is empty
	result = peekTail(qPtr, &data);
	if (result != PEEK_EMPTY_DEQ)
	{
		printf("Error: should have detected attempt to peek at the tail of an empty queue\n");
	}
	else
	{
		printf("Correctly identified attempt to peek at the tail of an empty queue\n");
	}

	// add a node to the head of the queue
	result = pushHead(qPtr, 25); 
	if (result != SUCCESS)
	{
		printf("Error: failed to add node to head of queue\n");
	}
	else
	{
		printf("pushHead() successful\n");
	}

	// add a node to the tail of the queue
	result = pushTail(qPtr, 35); 
	if (result != SUCCESS)
	{
		printf("Error: failed to add node to tail of queue\n");
	}
	else
	{
		printf("pushTail() successful\n");
	}

	// try peeking at the head of the queue - expect to find the value '25' there
	result = peekHead(qPtr, &data);
	if (result == PEEK_EMPTY_DEQ)
	{
		printf("Error: attempt to peek at the head of an empty queue\n");
	}
	else
	{
		if (data != 25)
		{
			printf("Error: data at head doesn't match\n");
		}
		else
		{
			printf("peekHead() successful\n");
		}
	}

	// try peeking at the tail of the queue - expect to find value 35 there
	result = peekTail(qPtr, &data);
	if (result == PEEK_EMPTY_DEQ)
	{
		printf("Error: attempt to peek at the tail of an empty queue\n");
	}
	else
	{
		if (data != 35)
		{
			printf("Error: data at tail doesn't match\n");
		}
		else
		{
			printf("peekTail() successful\n");
		}
	}

	// try popping from the queue
	result = popHead(qPtr, &data);
	if (result != SUCCESS)
	{
		printf("Error: failed to pop from queue\n");
	}
	else
	{
		printf("popHead() successful\n");
	}

	// try emptying the queue
	result = freeDEQueue(qPtr);
	if (result != SUCCESS)
	{
		printf("Error: failed to free queue\n");
	}
	else
	{
		printf("freeDEQueue() successful\n");
	}

	return 0;
}