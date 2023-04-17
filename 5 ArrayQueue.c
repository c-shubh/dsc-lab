#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct QueueADT
{
	int *list;
	int front;
	int rear;
	int capacity;
};
typedef struct QueueADT Queue;

Queue *create(int cap)
{
	// allocate memory for whole
	Queue *pthis = (Queue *)malloc(sizeof(Queue));
	// initialize members
	pthis->front = 0;
	pthis->rear = -1;
	pthis->capacity = cap;
	// allocate memory for part
	pthis->list = (int *)malloc(cap * sizeof(int));
	return pthis;
}

void destroy(Queue *pthis)
{
	free(pthis->list); // release part
	free(pthis); // release whole
}

bool enqueue(Queue *pthis, int elem)
{
	// check queue full
	if(pthis->rear + 1 == pthis->capacity)
		return false;

	pthis->rear++; // increment rear
	pthis->list[pthis->rear] = elem; // assign element
	return true; 
}

bool dequeue(Queue *pthis, int *pDel)
{
	// check Queue empty
	if(pthis->front > pthis->rear)
		return false;
	// save data to be deleted
	*pDel = pthis->list[pthis->front];
	// increment front
	pthis->front++;
	return true;
}

void display(const Queue *pthis)
{
	for(int i=pthis->front; i<=pthis->rear; i++)
		printf("%d ", pthis->list[i]);
	printf("\n");	
}

void inputElement(int *elem)
{
	printf("Enter element: ");
	scanf("%d", elem);
}

int main(void)
{
	int option, capacity;
	int elem, delElem;
	
	printf("Enter capacity: ");
	scanf("%d", &capacity);
	
	Queue *pq = create(capacity);
	
	while(true)
	{
		printf("\n1. Enqueue\n2. Dequeue\n3. Display\n4. Exit\n");
		printf("Select an option: ");
		scanf("%d", &option);
		printf("\n");
		
		switch(option)
		{
			case 1:
				inputElement(&elem);
				if(!enqueue(pq, elem))
					printf("Enqueue failed: %d\n", elem);
				break;
			case 2:
				if(dequeue(pq, &delElem))
					printf("Dequeued: %d\n", delElem);
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
