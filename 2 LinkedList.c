#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct NodeType
{
	int data;
	struct NodeType *link;
};
typedef struct NodeType Node;

Node *createNode(int data)
{
	// allocate memory for Node
	Node *newNode = (Node *)malloc(sizeof(Node));
	// initialize members
	newNode->data = data;
	newNode->link = NULL;
	return newNode;
}

struct LinkedListADT
{
	Node *head;
};
typedef struct LinkedListADT LinkedList;

LinkedList *create(void)
{
	// allocate memory for LL
	LinkedList *pthis = (LinkedList *)malloc(sizeof(LinkedList));
	// initialize members
	pthis->head = NULL;
	return pthis;	
}

int size(const LinkedList *pthis)
{
	int count = 0;
	Node *cursor = pthis->head;
	while(cursor != NULL)
	{
		count++;
		cursor = cursor->link;
	}
	return count;
}

bool insertBeg(LinkedList *pthis, int data)
{
	// create new node with data
	Node *pNew = createNode(data);
	// insert new node prior to head
	pNew->link = pthis->head;
	// new node is the head now
	pthis->head = pNew;
	return true;
}

bool append(LinkedList *pthis, int data)
{
	// create new node with data
	Node *pNew = createNode(data);
	// if LL is empty, new node is head
	if(pthis->head == NULL)
	{
		pthis->head = pNew;
		return true;	
	}
	
	Node *last = pthis->head; // start from head
	// after loop `last` will be at the last node
	while(last->link != NULL)
		last = last->link; // update last
	// link pNew to the last node	
	last->link = pNew;
	return true;
}

bool insertAt(LinkedList *pthis, int pos, int data)
{
	// check if LL is empty
	if(pthis->head == NULL)
		return false;
		
	// bounds check: valid bounds are [0...size]
	if(pos < 0 || pos > size(pthis))
		return false;
	
	if(pos == 0)
		return insertBeg(pthis, data);
	
	Node *cursor = pthis->head;
	// position cursor to (pos-1)th node
	for(int i=0; i<pos-1; i++)
		cursor = cursor->link;
	// create new node with data
	Node *pNew = createNode(data);
	// place pNew between pos-1 and pos th node
	pNew->link = cursor->link;
	cursor->link = pNew;
	return true;
}

bool deleteBeg(LinkedList *pthis, int *pData)
{
	// check if LL is empty
	if(pthis->head == NULL)
		return false;
	// store data to pass by ref variable
	*pData = pthis->head->data;
	// head is to be deleted
	Node *pDel = pthis->head;
	// logical deletion
	pthis->head = pDel->link;
	free(pDel); // physical deletion
	return true;
}

bool deleteEnd(LinkedList *pthis, int *pData)
{
	// check if LL is empty
	if(pthis->head == NULL)
		return false;
	
	// LL contains one node i.e. head
	if(pthis->head->link == NULL)
	{
		// head is to be deleted
		return deleteBeg(pthis, pData);
	}
		
	Node *lbo = pthis->head; // start from head
	// after loop `lob` will point to last but one node
	while(lbo->link->link != NULL)
		lbo = lbo->link;
	// last node is to be deleted
	Node *pDel = lbo->link;
	// store data to pass by ref variable
	*pData = pDel->data;
	lbo->link = NULL; // logical deletion
	free(pDel); // physical deletion
	return true;
}

bool deleteAt(LinkedList *pthis, int pos, int *pData)
{
	// check if LL is empty
	if(pthis->head == NULL)
		return false;
		
	// bounds check: valid bounds are [0...size-1]
	if(pos < 0 || pos >= size(pthis))
		return false;
	
	if(pos == 0)
		return deleteBeg(pthis, pData);
		
	Node *cursor = pthis->head;
	// position cursor to (pos-1)th node
	for(int i=0; i<pos-1; i++)
		cursor = cursor->link;
	// pos th node is to be deleted
	Node *pDel = cursor->link;
	// store data to pass by ref variable
	*pData = pDel->data;
	
	// logical deletion
	cursor->link = pDel->link;
	// physical deletion
	free(pDel);	

	return true;
	
}

void destroy(LinkedList *pthis)
{
	int temp;
	while(pthis->head != NULL) // while list is not empty
		deleteBeg(pthis, &temp); // delete elements
	free(pthis); // free LL
}

void display(const LinkedList *pthis)
{
	// start cursor at head
	Node *cursor = pthis->head;
	while(cursor != NULL) // loop till end of LL
	{
		printf("%d", cursor->data);
		if(cursor->link != NULL)
			printf(" -> ");
		cursor = cursor->link; // update cursor
	}
	putchar('\n');
}

void inputElement(int *elem)
{
	printf("Enter element: ");
	scanf("%d", elem);
}

void inputIndex(int *index)
{
	printf("Enter index: ");
	scanf("%d", index);
}


int main(void)
{
	LinkedList *ll = create();
	int option, elem, index, delElem;
	bool res;
	
	while(true)
	{
		printf("\n1) Insert\n2) Delete\n3) Display\n4) Exit\nSelect an option: ");
		scanf("%d", &option);
		
		switch(option)
		{
			case 1:
				inputElement(&elem);
				inputIndex(&index);
				if(index == 0) res = insertBeg(ll, elem);
				else if(index == size(ll)) res = append(ll, elem);
				else res = insertAt(ll, index, elem);
				if(!res)
					printf("Insertion failed\n");
				break;
			case 2:
				inputIndex(&index);
				if(index == 0) res = deleteBeg(ll, &delElem);
				else if(index == size(ll)-1) res = deleteEnd(ll, &delElem);
				else res = deleteAt(ll, index, &delElem);
				if(res)
					printf("Deleted %d\n", delElem);
				else printf("Deletion failed\n");
				break;
			case 3:
				display(ll);
				break;
			case 4:
				destroy(ll);
				return 0;
			default:
				printf("Invalid option\n");
		}
	}
	return 0;
}
