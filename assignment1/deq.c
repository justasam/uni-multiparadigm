/*
  Name: Justas Samuolis
  Matric number: 170020434
  Module code: AC21008
*/

#include "deq.h"
#include <stdlib.h>

// initialise a new Double Ended Queue (DEQueue)
// Parameters:
// qPtr - will receive a pointer to the newly allocated DEQueue
int initDEQueue(DEQueue **qPtr) {
  // Make sure that we are provided
  //  memory address of a DEQ pointer var.
  if (qPtr == NULL)
    return NULL_PARAM;

  // Make sure that DEQueue hasn't been initialised already
  if (*qPtr != NULL)
    return BAD_INIT_PARAM;

  // allocate memory for a new DEQueue and store in the pointer provided
  (*qPtr) = (DEQueue*)myMalloc(sizeof(DEQueue));

  // check for memory failure
  if ((*qPtr) == NULL)
    return OUT_OF_MEMORY;

  // initialise fields in the DEQueue
  (*qPtr)->head = NULL;
  (*qPtr)->tail = NULL;

  return SUCCESS;
}

// push a value onto the head of the DEQueue
// Parameters:
// qPtr - a pointer to the DEQueue
// data - the value to be pushed
int pushHead(DEQueue *qPtr, int data) {
  // check that we have a pointer to a valid DEQueue
  if (qPtr == NULL)
    return NULL_PARAM;

  // create a new node
  Node *newNode = (Node*)myMalloc(sizeof(Node));

  // check for memory failure
  if (newNode == NULL)
    return OUT_OF_MEMORY;

  // init fields in new node
  newNode->data = data;

  // set next to point to whatever is at the current head of queue
  newNode->next = qPtr->head;

  // make newNode new head of the stack
  qPtr->head = newNode;
  // if the DEQueue tail empty, it also becomes new tail of the stack
  if (qPtr->tail == NULL) {
    qPtr->tail = newNode;
  }

  return SUCCESS;
}

// push a value onto the tail of the DEQueue
// Parameters:
// qPtr - a pointer to the DEQueue
// data - the value to be pushed
int pushTail(DEQueue *qPtr, int data) {
  // check that we have a pointer to a valid DEQueue
  if (qPtr == NULL)
    return NULL_PARAM;

  // create a new node
  Node *newNode = (Node*)myMalloc(sizeof(Node));

  // check for memory failure
  if (newNode == NULL)
    return OUT_OF_MEMORY;

  // init fields in new node
  newNode->data = data;

  // set next to point to NULL (it's currently the last item in queue)
  newNode->next = NULL;

  // make newNode new tail of the stack
  qPtr->tail = newNode;
  // if the DEQueue head empty, it also becomes new head of the stack
  if (qPtr->head == NULL) {
    qPtr->head = newNode;
  }
  // if the DEQueue head has no next
  // it also becomes the next of the head
  else if (qPtr->head->next == NULL) {
    qPtr->head->next = newNode;
  }
  
  return SUCCESS;
}

// pop a value off the head of the DEQueue
// Parameters:
// qPtr - a pointer to the DEQueue
// data - will receive the value popped
int popHead(DEQueue *qPtr, int *data) {
  // check that we have a pointer to a valid DEQueue
  // and the pointer to store value into isn't null
  if (qPtr == NULL || data == NULL)
    return NULL_PARAM;

  // check if the DEQueue is currently empty
  if (qPtr->head == NULL)
    return POP_EMPTY_DEQ;
  
  // otherwise, store the val at the head of the DEQueue
  *data = qPtr->head->data;

  // create a temp pointer to the node currently
  // at the head of DEQueue (we are going to remove it)
  Node *nodeToRemove = qPtr->head;

  // change the top of the DEQueue to now be the next
  // node down
  qPtr->head = qPtr->head->next;
  
  // check whether tail is identical to the head
  // if so, tail also needs to be removed
  if (qPtr->tail == nodeToRemove)
    qPtr->tail = qPtr->tail->next;

  // remove / free the existing head (which has now been popped)
  nodeToRemove->next = NULL;
  nodeToRemove->data = 0;
  free(nodeToRemove);
  
  return SUCCESS;
}

// get the value at the head of the DEQueue
// Parameters:
// qPtr - a pointer to the DEQueue
// data - will receive the peeked value
int peekHead(DEQueue *qPtr, int *data) {
  // check that we have a pointer to a valid DEQueue
  // and the pointer to store value into isn't null
  if (qPtr == NULL || data == NULL)
    return NULL_PARAM;

  // check if the head is empty
  if (qPtr->head == NULL)
    return PEEK_EMPTY_DEQ;

  // otherwise, store the value that's in the node
  // at the head of the stack
  *data = qPtr->head->data;

  return SUCCESS;
}

// get the value at the tail of the DEQueue
// Parameters:
// qPtr - a pointer to the DEQueue
// data - will receive the peeked value
int peekTail(DEQueue *qPtr, int *data) {
  // check that we have a pointer to a valid DEQueue
  // and the pointer to store value into isn't null
  if (qPtr == NULL || data == NULL)
    return NULL_PARAM;

  // check if the tail is empty
  if (qPtr->tail == NULL)
    return PEEK_EMPTY_DEQ;

  // otherwise, store the value that's in the node
  // at the tail of the stack
  *data = qPtr->tail->data;

  return SUCCESS;
}

// free all memory used by DEQueue
// Parameters:
// qPtr - a pointer to the DEQueue to free
int freeDEQueue(DEQueue *qPtr) {
  // check that we have a pointer to valid DEQueue
  if (qPtr == NULL)
    return NULL_PARAM;

  // for holding pop value
  int poppedValue;

  // while popHead returns SUCCESS
  // which means that DEQueue is not empty yet
  while (popHead(qPtr, &poppedValue) == SUCCESS) {
    // do nothing - each cycle of the loop
    // pops the next value until it is empty
  }

  // then free the DEQueue itself
  free(qPtr);

  return SUCCESS;
}