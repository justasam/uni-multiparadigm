#include<stddef.h>

// error codes
#define SUCCESS				100	// operation completed successfully
#define BAD_INIT_PARAM		101 // bad initialisation parameter - a parameter provided to an initialisation function is invalid
#define OUT_OF_MEMORY		102 // memory allocation failure
#define NULL_PARAM			103 // a parameter provided to a function is NULL (where non-NULL is expected)
#define BAD_DEQ				104 // a malformed double-ended queue is detected
#define POP_EMPTY_DEQ		105 // attempt to pop from an empty queue
#define PEEK_EMPTY_DEQ		106 // attempt to peek into an empty queue


/* typedef for the nodes in a double ended queue. */
typedef struct Node{
	int data;
	struct Node* next;
} Node;


/* typedef for the Double-ended (DE) Queue itself. */
typedef struct DEQueue{
	Node* head;
	Node* tail;
} DEQueue;


/* Initialize a new DEQueue and record its pointer into (*qPtr).
		qPtr must not be NULL
		(*qPtr) must be NULL */
int initDEQueue(DEQueue **qPtr);


/* Push 'data' onto the head of the queue.
		qPtr must not be NULL
		data can be any valid value */
int pushHead(DEQueue *qPtr, int data);


/* Push 'data' onto the tail of the queue
		qPtr must not be NULL
		data can be any valid value */
int pushTail(DEQueue *qPtr, int data);


/* Pop the head off the queue and record data in (*dataPtr).
		qPtr must not be NULL
		dataPtr must not be NULL */
int popHead(DEQueue* qPtr, int* dataPtr);


/* Peek the head of the queue and record in (*dataPtr).
		qPtr must not be NULL
		dataPtr must not be NULL */
int peekHead(DEQueue* qPtr, int* dataPtr);


/* Peek the tail of the queue and record in (*dataPtr).
		qPtr must not be NULL
		dataPtr must not be NULL */
int peekTail(DEQueue* qPtr, int* dataPtr);


/* Free all memory used by the queue.
		qtr must not be NULL */
int freeDEQueue(DEQueue* qPtr);


/* We define this function in 'deq_tester.c'.
   Always use this function to request memory.
   Use it, but don't define it. */
void* myMalloc(size_t size);
