#include <stdio.h>
#include <stdlib.h>
#include "deq.h"

#define	WIN  0
#define	FAIL 9999

/* A function (and global) that can trigger malloc fails on demand. */
int mallocFail = 0;
void* myMalloc(size_t size) {
	if (mallocFail) { return NULL; }
	else { return malloc(size); }
}

int test_initDEQueue();
int test_pushHead();
int test_pushTail();
int test_popHead();
int test_peekHead();
int test_peekTail();
int test_freeDEQueue();

int main() {
	if (test_initDEQueue() != 0) {
		printf("Quitting testing: 'initDEQueue' failed.\n");
		return 0;
	}
	if (test_pushHead() != 0) {
		printf("Quitting testing: 'pushHead' failed.\n");
		return 0;
	}
	if (test_pushTail() != 0) {
		printf("Quitting testing: 'pushTail' failed.\n");
		return 0;
	}
	if (test_popHead() != 0) {
		printf("Quitting testing: 'popHead' failed.\n");
		return 0;
	}
	if (test_peekHead() != 0) {
		printf("Quitting testing: 'peekHead' failed.\n");
		return 0;
	}
	if (test_peekTail() != 0) {
		printf("Quitting testing: 'peekTail' failed.\n");
		return 0;
	}
	if (test_freeDEQueue() != 0) {
		printf("Quitting testing: 'freeDEQueue' failed.\n");
		return 0;
	}
	return 0;
}

/* Test 'initDEQueue'.
** This function has a memory leak (deq is never free'd) but we
** haven't tested 'freeDEQueue' yet, so can't exactly use it here. */
int test_initDEQueue() {
	printf("Testing initDEQueue...\n");

	// test for NULL_PARAM check
	int rVal = initDEQueue(NULL);
	if (rVal != NULL_PARAM) { printf("  failed: make sure that input into 'initDEQueue' is not NULL\n"); return FAIL; }

	// BAD_INIT_PARAM]
	DEQueue *qPtr = NULL;
	int thing = 71;
	qPtr = (DEQueue*)&thing; // deliberately make qPtr non-null so it appears it is already allocated to something valid
	rVal = initDEQueue(&qPtr);
	if (rVal != BAD_INIT_PARAM) { printf("  failed: make sure queue pointer passed to initDEQueue is NULL\n"); return FAIL; }

	// OUT_OF_MEMORY
	mallocFail = 1;
	qPtr = NULL;
	rVal = initDEQueue(&qPtr);
	if (rVal != OUT_OF_MEMORY) { printf("  failed: should always check return from malloc (myMalloc)\n"); return FAIL; }
	mallocFail = 0;

	// SUCCESS
	qPtr = NULL;
	rVal = initDEQueue(&qPtr);
	if (qPtr->head != NULL) { printf("  failed: queue's head pointer not set to NULL in initDEQueue\n"); return FAIL; }
	if (qPtr->tail != NULL) { printf("  failed: queue's tail pointer not set to NULL in initDEQueue\n"); return FAIL; }
	if (rVal != SUCCESS) { printf("  failed: did not return SUCCESS in initDEQueue: %d\n", rVal); return FAIL; }
	else /* (rVal == SUCCESS) */ { printf("  succeeded\n"); return WIN; }
}

/* Test 'pushHead'.
** This function has a memory leak (deq is never free'd) but we
** haven't tested 'freeDEQueue' yet, so can't exactly use it here. */
int test_pushHead() {
	printf("Testing pushHead...\n");

	// initialize a new queue to test on
	DEQueue *qPtr = NULL;
	int rVal = initDEQueue(&qPtr);
	if (rVal != SUCCESS) { printf("  initialize 1 (initDEQueue) failed: %d\n", rVal); return FAIL; }

	// NULL_PARAM 1 [should fail]
	int aNumber = 88;
	rVal = pushHead(NULL, aNumber);
	if (rVal != NULL_PARAM) { printf("  failed: should make sure queue pointer is not NULL\n"); return FAIL; }

	// OUT_OF_MEMORY
	mallocFail = 1;
	rVal = pushHead(qPtr, aNumber);
	if (rVal != OUT_OF_MEMORY) { printf("  failed: should always check return from malloc (myMalloc)\n"); return FAIL; }
	mallocFail = 0;

	// push a single item onto empty queue
	rVal = pushHead(qPtr, aNumber);	
	if (qPtr->head == NULL) { printf("  'head of queue should not be NULL after push\n"); return FAIL; }
	if (qPtr->tail == NULL) { printf("  'tail of queue should not be NULL after push\n"); return FAIL; }
	if (qPtr->head != qPtr->tail) { printf("  head should equal tail after push onto empty queue\n"); return FAIL; }
	if (qPtr->head->next != NULL) { printf("  head's next should be NULL after push onto empty queue\n"); return FAIL; }
	if (qPtr->head->data != aNumber) { printf("  data in pushed node doesn't match\n"); return FAIL; }
	if (rVal != SUCCESS) { printf("  pushHead did not return SUCCESS: %d\n", rVal); return FAIL; }

	// test a second pushHeads (push onto non-empty deq)
	// initialize a new queue to test on
	qPtr = NULL;		// this introduces a memory leak - no 'free' tested yet
	rVal = initDEQueue(&qPtr);	// should be safe, but could have run out of memory
	if (rVal != SUCCESS) { printf("  initialize 2 (initDEQueue) failed: %d\n", rVal); return FAIL; }

	// push first item and grab it's Node
	int v1 = 35;
	pushHead(qPtr, v1);	// will work (because tests above passed)
	Node* node1 = qPtr->head;
	// then push another one - this is what we're testing now
	int v2 = 88;
	rVal = pushHead(qPtr, v2);	// this is what we're testing now

	// see what we've got after inserting two values
	if (qPtr->head == NULL) { printf("  failed: head should not be NULL\n"); return FAIL; }
	if (qPtr->tail == NULL) { printf("  failed: tail should not be NULL\n"); return FAIL; }
	if (qPtr->head == qPtr->tail) { printf("  failed: head should not equal tail in queue with more than 1 node\n"); return FAIL; }
	if (qPtr->tail != node1) { printf("  failed: tail should be first pushed Node\n"); return FAIL; }
	if (qPtr->tail->next != NULL) { printf("  failed: tail's next should equal NULL\n"); return FAIL; }
	if (qPtr->tail->data != v1) { printf("  failed: tail node did not record data parameter correctly\n"); return FAIL; }
	if (qPtr->head->next != qPtr->tail) { printf("  failed: next node after head should be tail in 2 node queue\n"); return FAIL; }
	if (qPtr->head->data != v2) { printf("  failed: head did not record data parameter correctly\n"); return FAIL; }
	if (rVal != SUCCESS) { printf("  failed: did not return SUCCESS: %d\n", rVal); return FAIL; }
	else /* (rVal == SUCCESS) */ { printf("  succeeded\n"); return WIN; }
}

/* Test 'pushTail'.
** This function has a memory leak (deq is never free'd) but we
** haven't tested 'freeDEQueue' yet, so can't exactly use it here. */
int test_pushTail() {
	printf("Testing pushTail...\n");

	// initialize a new queue to test on
	DEQueue *qPtr = NULL;
	int rVal = initDEQueue(&qPtr);
	if (rVal != SUCCESS) { printf("  initialize 1 (initDEQueue) failed: %d\n", rVal); return FAIL; }

	// NULL_PARAM 1 [should fail]
	int aNumber = 99;
	rVal = pushTail(NULL, aNumber);
	if (rVal != NULL_PARAM) { printf("  failed: should make sure queue pointer passed into initDEQueue is not NULL\n"); return FAIL; }

	// OUT_OF_MEMORY
	mallocFail = 1;
	rVal = pushTail(qPtr, aNumber);
	if (rVal != OUT_OF_MEMORY) { printf("  failed: should always check return from malloc (myMalloc)\n"); return FAIL; }
	mallocFail = 0;

	// push a single item onto empty  queue
	rVal = pushTail(qPtr, aNumber);	// push NULL onto empty deq
	if (qPtr->head == NULL) { printf("  'head should not be NULL after push\n"); return FAIL; }
	if (qPtr->tail == NULL) { printf("  'tail should not be NULL after push\n"); return FAIL; }
	if (qPtr->head != qPtr->tail) { printf("  head should equal tail after push onto empty deq\n"); return FAIL; }
	if (qPtr->tail->next != NULL) { printf("  tail's next should be NULL after push onto empty deq\n"); return FAIL; }
	if (qPtr->tail->data != aNumber) { printf("  tail's data doesn't match\n"); return FAIL; }
	if (rVal != SUCCESS) { printf("  pushTail did not return SUCCESS: %d\n", rVal); return FAIL; }

	// test a second pushTail (push onto non-empty queue)
	// initialize a new queue to test on
	qPtr = NULL;		// this introduces a memory leak - no 'free' tested yet
	rVal = initDEQueue(&qPtr);	// should be safe, but could have run out of memory
	if (rVal != SUCCESS) { printf("  initialize 2 (initDEQueue) failed: %d\n", rVal); return FAIL; }

	// push first item and grab it's Node
	int v1 = 35;
	pushTail(qPtr, v1);	// will work (because tests above passed)
	Node* node1 = qPtr->tail;
	// then push another one - this is what we're testing now
	int v2 = 88;
	rVal = pushTail(qPtr, v2);	// this is what we're testing now

	// see what we've got after inserting two values
	if (qPtr->head == NULL) { printf("  failed: head should not be NULL\n"); return FAIL; }
	if (qPtr->tail == NULL) { printf("  failed: tail should not be NULL\n"); return FAIL; }
	if (qPtr->head == qPtr->tail) { printf("  failed: head should not equal 'tail'\n"); return FAIL; }
	if (qPtr->head != node1) { printf("  failed: head should be first push Node\n"); return FAIL; }
	if (qPtr->tail->next != NULL) { printf("  failed: tail's next should equal NULL\n"); return FAIL; }
	if (qPtr->tail->data != v2) { printf("  failed: tail did not record data parameter\n"); return FAIL; }
	if (qPtr->head->next != qPtr->tail) { printf("  failed: head's next should equal tail\n"); return FAIL; }
	if (qPtr->head->data != v1) { printf("  failed: head did not record data parameter\n"); return FAIL; }
	if (rVal != SUCCESS) { printf("  failed: did not return SUCCESS: %d\n", rVal); return FAIL; }
	else /* (rVal == SUCCESS) */ { printf("  succeeded\n"); return WIN; }
}

/* Test 'popHead'.
** This function has a memory leak (deq is never free'd) but we
** haven't tested 'freeDEQueue' yet, so can't exactly use it here. */
int test_popHead() {
	printf("Testing popHead...\n");

	// initialize a new deq to test on
	DEQueue* qPtr = NULL;
	int rVal = initDEQueue(&qPtr);
	if (rVal != SUCCESS) { printf("  initialize 1 (initDEQueue) failed: %d\n", rVal); return FAIL; }

	// test NULL_PARAMs
	int data;
	rVal = popHead(NULL, &data);
	if (rVal != NULL_PARAM) { printf("  failed: should make sure pointer to queue is not NULL\n"); return FAIL; }
	rVal = popHead(qPtr, NULL);
	if (rVal != NULL_PARAM) { printf("  failed: should make sure pointer to data param is not NULL\n"); return FAIL; }

	// test pop from empty queue
	rVal = popHead(qPtr, &data);
	if (rVal != POP_EMPTY_DEQ) { printf("  failed: should check for empty queue before any pop\n"); return FAIL; }

	// push one item
	int thing1 = 24;
	rVal = pushHead(qPtr, thing1);
	if (rVal != SUCCESS) { printf("  initialize 2 (pushHead) failed: %d\n", rVal); return FAIL; }

	// push another item
	int thing2 = 45;
	rVal = pushHead(qPtr, thing2);
	if (rVal != SUCCESS) { printf("  initialize 3 (pushHead) failed: %d\n", rVal); return FAIL; }

	// pop off the head
	rVal = popHead(qPtr, &data);
	if (qPtr->head == NULL) { printf("  head should not be NULL after pop when n>1\n"); return FAIL; }
	if (qPtr->tail == NULL) { printf("  tail should not be NULL after pop when n>1\n"); return FAIL; }
	if (qPtr->head != qPtr->tail) { printf("  head should equal tail after pop when n=2\n"); return FAIL; }
	if (qPtr->head->next != NULL) { printf("  head's next should be NULL after pop when n=2\n"); return FAIL; }
	if (qPtr->head->data != thing1) { printf("  'head's data should be %d after popping %d\n", thing1, thing2); return FAIL; }
	if (data != thing2) { printf("  'data should be %d after popping %d\n", thing2, thing2); return FAIL; }
	if (rVal != SUCCESS) { printf("  failed: did not return SUCCESS\n"); return FAIL; }

	// pop to make an empty queue
	rVal = popHead(qPtr, &data);
	if (qPtr->head != NULL) { printf("  head should be NULL after pop when n=1\n"); return FAIL; }
	if (qPtr->tail != NULL) { printf("  tail should be NULL after pop when n=1\n"); return FAIL; }
	if (data != thing1) { printf("  data should be %d after popping %d\n", thing1, thing1); return FAIL; }
	if (rVal != SUCCESS) { printf("  failed: did not return SUCCESS: %d\n", rVal); return FAIL; }
	else /* (rVal == SUCCESS) */ { printf("  succeeded\n"); return WIN; }
}

/* Test 'peekHead'.
** This function has a memory leak (deq is never free'd) but we
** haven't tested 'freeDEQueue' yet, so can't exactly use it here. */
int test_peekHead() {
	printf("Testing peekHead...\n");

	// initialize a new queue to test on
	DEQueue* qPtr = NULL;
	int rVal = initDEQueue(&qPtr);
	if (rVal != SUCCESS) { printf("  initialize 1 (initDEQueue) failed: %d\n", rVal); return FAIL; }

	// test NULL_PARAMs
	int data;
	rVal = peekHead(NULL, &data);
	if (rVal != NULL_PARAM) { printf("  failed: should make sure queue pointer is not NULL\n"); return FAIL; }
	rVal = peekHead(qPtr, NULL);
	if (rVal != NULL_PARAM) { printf("  failed: should make sure pointer to data param is not NULL\n"); return FAIL; }

	// test peek from empty deq
	rVal = peekHead(qPtr, &data);
	if (rVal != PEEK_EMPTY_DEQ) { printf("  failed: should check for empty deq before any peek\n"); return FAIL; }

	// push one item
	int thing1 = 23;
	rVal = pushHead(qPtr, thing1);
	if (rVal != SUCCESS) { printf("  initialize 2 (pushHead) failed: %d\n", rVal); return FAIL; }

	// peek that item
	rVal = peekHead(qPtr, &data);	
	if (data != thing1) { printf("  data should be %d after pushing %d\n", thing1, thing1); return FAIL; }
	if (rVal != SUCCESS) { printf("  failed: did not return SUCCESS: %d\n", rVal); return FAIL; }

	// push another item
	int thing2 = 12;
	rVal = pushHead(qPtr, thing2);
	if (rVal != SUCCESS) { printf("  initialize 3 (pushHead) failed: %d\n", rVal); return FAIL; }

	// peek the second item	
	rVal = peekHead(qPtr, &data);	
	if (data != thing2) { printf("  data should be %d after pushing %d\n", thing2, thing2); return FAIL; }
	if (rVal != SUCCESS) { printf("  failed: did not return SUCCESS: %d\n", rVal); return FAIL; }
	else /* (rVal == SUCCESS) */ { printf("  succeeded\n"); return WIN; }
}

/* Test 'peekTail'.
** This function has a memory leak (deq is never free'd) but we
** haven't tested 'freeDEQueue' yet, so can't exactly use it here. */
int test_peekTail() {
	printf("Testing peekTail...\n");

	// initialize a new queue to test on
	DEQueue* qPtr = NULL;
	int rVal = initDEQueue(&qPtr);
	if (rVal != SUCCESS) { printf("  initialize 1 (initDEQueue) failed: %d\n", rVal); return FAIL; }

	// test NULL_PARAMs
	int data;
	rVal = peekTail(NULL, &data);
	if (rVal != NULL_PARAM) { printf("  failed: should make sure queue pointer is not NULL\n"); return FAIL; }
	rVal = peekTail(qPtr, NULL);
	if (rVal != NULL_PARAM) { printf("  failed: should make sure data pointer parameter is not NULL\n"); return FAIL; }
	

	// test peek from empty deq
	rVal = peekTail(qPtr, &data);
	if (rVal != PEEK_EMPTY_DEQ) { printf("  failed: should check for empty deq before any peek\n"); return FAIL; }

	// push one item
	int thing1 = 76;
	rVal = pushTail(qPtr, thing1);
	if (rVal != SUCCESS) { printf("  initialize 2 (pushTail) failed: %d\n", rVal); return FAIL; }

	// peek that item
	rVal = peekTail(qPtr, &data);	
	if (data != thing1) { printf("  data should be %d after pushing %d\n", thing1, thing1); return FAIL; }
	if (rVal != SUCCESS) { printf("  failed: did not return SUCCESS: %d\n", rVal); return FAIL; }

	// push another item
	int thing2 = 32;
	rVal = pushTail(qPtr, thing2);
	if (rVal != SUCCESS) { printf("  initialize 3 (pushTail) failed: %d\n", rVal); return FAIL; }

	// peek the second item	
	rVal = peekTail(qPtr, &data);	
	if (data != thing2) { printf("  data should be %d after pushing %d\n", thing2, thing2); return FAIL; }
	if (rVal != SUCCESS) { printf("  failed: did not return SUCCESS: %d\n", rVal); return FAIL; }
	else /* (rVal == SUCCESS) */ { printf("  succeeded\n"); return WIN; }
}

/* Test 'freeDEQueue'.
   Weird tests because I can't verify that 'free' ran - the pointers remain... */
int test_freeDEQueue() {
	printf("Testing freeDEQueue...\n");

	// test for NULL_PARAM check
	int rVal = freeDEQueue(NULL);
	if (rVal != NULL_PARAM) { printf("  failed: should make sure queue is not NULL before attempting to free it\n"); return FAIL; }	
	
	// test freeing empty queue
	DEQueue* qPtr = NULL;
	rVal = initDEQueue(&qPtr);
	if (rVal != SUCCESS) { printf("  initialize 1 (initDEQueue) failed: %d\n", rVal); return FAIL; }
	rVal = freeDEQueue(qPtr);
	if (rVal != SUCCESS) { printf("  failed 1 - attempting to free an empty queue: with error %d\n", rVal); return FAIL; }

	// test freeing !empty queue
	qPtr = NULL;
	rVal = initDEQueue(&qPtr);
	if (rVal != SUCCESS) { printf("  initialize 3 (initDEQueue) failed: %d\n", rVal); return FAIL; }
	int v1 = 24; 
	rVal = pushHead(qPtr, v1);
	if (rVal != SUCCESS) { printf("  pushHead 3 (pushHead) failed: %d\n", rVal); return FAIL; }
	rVal = freeDEQueue(qPtr);
	if (rVal != SUCCESS) { printf("  failed 3 to free non-empty queue with errro code %d\n", rVal); return FAIL; }
	else /* (rVal == SUCCESS) */ { printf("  succeeded\n"); return WIN; }
}
