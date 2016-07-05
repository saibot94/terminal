#include "list.h"



List* listCreate()
{
	 List* list = (List*)(malloc(sizeof(List)));
	 list->head = NULL;
	 list->tail = NULL;
	return list;
}

ListNode* listGetHead(List* list)
{
	return list->head;
}

ListNode* listGetTail(List* list)
{
	return list->tail;
}

void* listPopHead(List* list)
{
	ListNode* node = list->head;
	if(node != NULL)
	{
		list->head = list->head->next;		
	}
	return node->item;
}

void* listPopTail(List* list)
{
	ListNode* node = list->head;
	if(node != NULL)
	{
		list->head = list->head->next;		
	}
	return node->item;
}


void* listPeekHead(List* list)
{
	if(list->head!=NULL)
	{
		return list->head->item;
	}
	return NULL;
}

void* listPeekTail(List* list)
{
	if(list->tail!=NULL)
	{
		return list->tail->item;
	}
	return NULL;
}
void listInsertFront(List* linkedList, void* item)
{
	ListNode* node = (ListNode*)malloc(sizeof(ListNode));
	//memcpy(node->item, item, sizeof(*item));
	node->item = item;
	node->prev = NULL;
	node->next = NULL;
	if(linkedList->head == NULL)
	{
		linkedList->head = node;
		linkedList->tail = node;
	}
	else
	{
		node->next=linkedList->head;
		linkedList->head->prev=node;
		linkedList->head=node;
	}
}

void listInsertBack(List* linkedList, void* item)
{
	ListNode* node = (ListNode *)malloc(sizeof(ListNode));
	node->item = item;
	//memcpy(node->item, item, sizeof(item));
	node->next=NULL;
	node->prev=NULL;

	if (linkedList->head==NULL)
	{
		linkedList->head=node;
		linkedList->tail=node;
	}
	else
	{
		node->prev=linkedList->tail;
        linkedList->tail->next=node;
        linkedList->tail=node;
	}
}


void listClear(List* linkedList, int deleteItems)
{
	while(linkedList->head!=NULL)
	{
		if(deleteItems)
		{
			free(linkedList->head->item);			
		}
		free(linkedList->head);
		linkedList->head=linkedList->head->next;
	}

	linkedList->head=NULL;
	linkedList->tail=NULL;
}

int listIsEmpty(List* linkedList)
{
	if(listLength(linkedList) == 0)
	{
		return 1;
	}
	return 0;
}

int listLength(List* linkedList)
{
	int i = 0;
	ListNode* node = linkedList->head;
	while(node!= NULL)
	{
		i++;
		node=node->next;
	}
	return i;
}

void listPrint(List* linkedList)
{
	int i = 0;
	while(listLength(linkedList) != 0)
	{
		void* node = listPopHead(linkedList);
		if(node != NULL)
		{
			char* string = (char*)(node);
			printf("Value: %s \n",string);
		}
	}
}