#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct NodeType
{
	char data;
	struct NodeType *link;
};
typedef struct NodeType Node;

Node *createNode(char data)
{
	// allocate memory for Node
	Node *newNode = (Node *)malloc(sizeof(Node));
	// initialize members
	newNode->data = data;
	newNode->link = NULL;
	return newNode;
}

struct QueueADT
{
	Node *rear;
	Node *front;
};
typedef struct QueueADT Queue;

Queue *create(void)
{
	// allocate memory for Queue
	Queue *pthis = (Queue *)malloc(sizeof(Queue));
	// initialize members
	pthis->rear = NULL;
	pthis->front = NULL;
	return pthis;	
}

bool enqueue(Queue *pthis, char data)
{
	// create new node with data
	Node *pNew = createNode(data);
	
	// if Queue is empty
	if(pthis->front == NULL)
	{
		pthis->front = pthis->rear = pNew;
		return true;
	}	

	// insert new node after rear
	pthis->rear->link = pNew;
	// new node is the rear now
	pthis->rear = pNew;
	return true;
}

bool dequeue(Queue *pthis, char *pData)
{
	// check if Queue is empty
	if(pthis->front == NULL)
		return false;
	// store data to pass by ref variable
	*pData = pthis->front->data;
	// front is to be deleted
	Node *pDel = pthis->front;
	// logical deletion
	pthis->front = pDel->link;
	free(pDel); // physical deletion
	return true;
}

void destroy(Queue *pthis)
{
	char temp;
	while(pthis->front != NULL) // while list is not empty
		dequeue(pthis, &temp); // delete elements
	free(pthis); // free Queue
}

void display(const Queue *pthis)
{
	// start cursor at front
	Node *cursor = pthis->front;
	while(cursor != NULL) // loop till end of Queue
	{
		printf("%c ", cursor->data);
		cursor = cursor->link; // update cursor
	}
	putchar('\n');
}

void inputElement(char *elem)
{
	printf("Enter element: ");
	scanf("%c", elem);
	getchar(); // get rid of a newline after entering option
}

int main(void)
{
	int option;
	char elem, delElem;
	
	Queue *pq = create();
	
	while(true)
	{
		printf("\n1. Enqueue\n2. Dequeue\n3. Display\n4. Exit\n");
		printf("Select an option: ");
		scanf("%d", &option);
		getchar(); // get rid of a newline after entering option
		printf("\n");
		
		switch(option)
		{
			case 1:
				inputElement(&elem);
				if(!enqueue(pq, elem))
					printf("Enqueue failed: %c\n", elem);
				break;
			case 2:
				if(dequeue(pq, &delElem))
					printf("Dequeued: %c\n", delElem);
				else printf("Dequeue failed\n");
				break;
			case 3:
				display(pq);
				break;
			case 4:
				destroy(pq);
				return 0;
			default:
				printf("Invalid option: %d\n", option);
		}
	}
	
	printf("\n");
	return 0;
}
