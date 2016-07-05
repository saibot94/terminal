/* Header for a list of items */
#ifndef LIST_H
#define LIST_H 

#include <stdlib.h>
#include <string.h>
#include <stdio.h>


typedef struct ListNode
{
	void* item;
	struct ListNode* prev;
	struct ListNode* next;
} ListNode;


typedef struct List 
{
	struct ListNode* head;
	struct ListNode* tail;
} List;

List* listCreate();
ListNode* listGetHead(List*);
ListNode* listGetTail(List*);
void listPrint(List* linkedList);
void listInsertFront(List* , void* );
void listInsertBack(List* , void* );
void listClear(List*, int deleteItems);
int listIsEmpty(List*);
int listLength(List*);
void* listPopHead(List* list);
void* listPopTail(List* list);
void* listPeekHead(List* list);
void* listPeekTail(List* list);
#endif	
