/*
  Name: Justas Samuolis
  Matric number: 170020434
  Module code: AC21008
*/
#include "list.h"
#include <stdio.h>
#include <stdlib.h>

int listInit(List **listPtr) {

  if (listPtr == NULL)
    return NULL_PARAM;

  if (*listPtr != NULL)
    return BAD_INIT_PARAM;

  (*listPtr) = (List*)myMalloc(sizeof(List));

  if ((*listPtr) == NULL)
    return OUT_OF_MEMORY;
 
  (*listPtr)->head = NULL;
  (*listPtr)->curr = NULL;
  (*listPtr)->tail = NULL;

  return SUCCESS;
}

int insertBeforeCurr(List *listPtr, int data) {
  if (listPtr == NULL)
    return NULL_PARAM;

  ListNode *newNode = (ListNode*)myMalloc(sizeof(ListNode));

  if (newNode == NULL)
    return OUT_OF_MEMORY;

  newNode->data = data;
  newNode->next = NULL;
  newNode->prev = NULL;

  // if current is NULL (list is empty):
  if (listPtr->curr == NULL) {
    listPtr->curr = newNode;
    listPtr->head = newNode;
    listPtr->tail = newNode;
    return SUCCESS;
  }

  // if current is at the head
  if (listPtr->curr == listPtr->head && listPtr->curr->prev == NULL) {
    newNode->next = listPtr->curr;
    listPtr->curr->prev = newNode;
    listPtr->head = newNode;

    return SUCCESS;
  }
  // else
  if (listPtr->curr != listPtr->head && listPtr->curr->prev != NULL) {
    newNode->next = listPtr->curr;
    newNode->prev = listPtr->curr->prev;
    listPtr->curr->prev->next = newNode;
    listPtr->curr->prev = newNode;

    return SUCCESS;
  }

  return BAD_LIST;
}

int insertAfterCurr(List *listPtr, int data) {
  if (listPtr == NULL)
    return NULL_PARAM;

  ListNode *newNode = (ListNode*)myMalloc(sizeof(ListNode));

  if (newNode == NULL)
    return OUT_OF_MEMORY;

  newNode->data = data;
  newNode->next = NULL;
  newNode->prev = NULL;

  // if current is NULL (list is empty):
  if (listPtr->curr == NULL) {
    listPtr->curr = newNode;
    listPtr->head = newNode;
    listPtr->tail = newNode;
    return SUCCESS;
  }

  // if current is at the tail
  if (listPtr->curr == listPtr->tail && listPtr->curr->next == NULL) {
    newNode->prev = listPtr->curr;
    listPtr->curr->next = newNode;
    listPtr->tail = newNode;

    return SUCCESS;
  }
  // else
  if (listPtr->curr != listPtr->tail && listPtr->curr->next != NULL) {
    newNode->next = listPtr->curr->next;
    newNode->prev = listPtr->curr;
    listPtr->curr->next->prev = newNode;
    listPtr->curr->next = newNode;    
    
    return SUCCESS;
  }

  return BAD_LIST;
}

int currToPrev(List *listPtr) {
  if (listPtr == NULL)
    return NULL_PARAM;

  if (listPtr->curr == NULL)
    return MOVE_IN_EMPTY_LIST;

  if (listPtr->curr->prev != NULL && listPtr->head != listPtr->curr) {
    listPtr->curr = listPtr->curr->prev;
    return SUCCESS;
  }

  return MOVE_PREV_AT_HEAD;
}

int currToNext(List *listPtr) {
  if (listPtr == NULL)
    return NULL_PARAM;

  if (listPtr->curr == NULL)
    return MOVE_IN_EMPTY_LIST;

  if (listPtr->curr->next != NULL && listPtr->tail != listPtr->curr) {
    listPtr->curr = listPtr->curr->next;
    return SUCCESS;
  }
    
  return MOVE_NEXT_AT_TAIL;
}

int getDataAtCurr(List *listPtr, int *dataPtr) {
  if (listPtr == NULL || dataPtr == NULL)
    return NULL_PARAM;
  
  if (listPtr->curr == NULL)
    return GET_FROM_EMPTY_LIST;
  
  *dataPtr = listPtr->curr->data;

  return SUCCESS;
}

int removeAtCurr(List *listPtr, int *dataPtr, int moveForward) {
  if (listPtr == NULL || dataPtr == NULL)
    return NULL_PARAM;

  if (listPtr->curr == NULL)
    return REMOVE_FROM_EMPTY_LIST;

  ListNode *nodeToRemove = NULL;

  // 1 item list
  if (listPtr->head == listPtr->tail && listPtr->tail == listPtr->curr) {
    nodeToRemove = listPtr->curr;
    listPtr->head = NULL;
    listPtr->tail = NULL;
    listPtr->curr = NULL;
    *dataPtr = nodeToRemove->data;
    free(nodeToRemove);
    return SUCCESS;
  }

  // more than 1 item list
  // curr at head
  if (listPtr->curr == listPtr->head) {
    nodeToRemove = listPtr->curr;
    listPtr->head = nodeToRemove->next;
    listPtr->head->prev = NULL;
    listPtr->curr = listPtr->head;
    *dataPtr = nodeToRemove->data;
    free(nodeToRemove);
    return SUCCESS;
  }

  // curr at tail
  if (listPtr->curr == listPtr->tail) {
    nodeToRemove = listPtr->curr;
    listPtr->tail = nodeToRemove->prev;
    listPtr->tail->next = NULL;
    listPtr->curr = listPtr->tail;
    *dataPtr = nodeToRemove->data;
    free(nodeToRemove);
    return SUCCESS;
  }

  // curr between head & tail
  nodeToRemove = listPtr->curr;
  if (moveForward) {
    listPtr->curr = listPtr->curr->next;
    listPtr->curr->prev = nodeToRemove->prev;
    nodeToRemove->prev->next = listPtr->curr;
  }
  else {
    listPtr->curr = listPtr->curr->prev;
    listPtr->curr->next = nodeToRemove->next;
    nodeToRemove->next->prev = listPtr->curr;
  }

  *dataPtr = nodeToRemove->data;
  free(nodeToRemove);
  return SUCCESS;
}

int listFree(List *listPtr) {
  if (listPtr == NULL)
    return NULL_PARAM;

  int dataPtr;
  while (removeAtCurr(listPtr, &dataPtr, 0) != REMOVE_FROM_EMPTY_LIST) {

  }

  free(listPtr);

  return SUCCESS;
}