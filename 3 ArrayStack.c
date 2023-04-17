#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct StackADT
{
	int *list;
	int tos;
	int capacity;
};

typedef struct StackADT Stack;

Stack *create(int cap)
{
	// allocate memory for whole
	Stack *pthis = (Stack *)malloc(sizeof(Stack));
	// initialize members
	pthis->tos = -1;
	pthis->capacity = cap;
	// allocate memory for part
	pthis->list = malloc(cap*sizeof(int));
	return pthis;
}

void destroy(Stack *pthis)
{
	free(pthis->list); // release part
	free(pthis); // release whole
}

bool push(Stack *pthis, int elem)
{
	if(pthis->tos+1 == pthis->capacity)
		return false;
	pthis->tos++; // increment top index
	pthis->list[pthis->tos] = elem; // assign element
	return true; 
}

bool pop(Stack *pthis, int *pDel)
{
	// check array empty
	if(pthis->tos == -1)
		return false;
		
	// save data to be deleted
	*pDel = pthis->list[pthis->tos];
	
	// decrement tos
	pthis->tos--;
	return true;
}

bool peep(const Stack *pthis, int *top)
{
	// check array empty
	if(pthis->tos == -1)
		return false;
	*top = pthis->list[pthis->tos]; // save to pass by ref variable
	return true;
}

void display(const Stack *pthis)
{
	for(int i=pthis->tos; i>=0; i--)
		printf("%d\n", pthis->list[i]);
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
	
	Stack *sp = create(capacity);
	
	while(true)
	{
		printf("\n1. Push\n2. Pop\n3. Peep\n4. Display\n5. Exit\n");
		printf("Select an option: ");
		scanf("%d", &option);
		printf("\n");
		
		switch(option)
		{
			case 1:
				inputElement(&elem);
				if(!push(sp, elem))
					printf("Pushing failed\n");
				break;
			case 2:
				if(pop(sp, &delElem))
					printf("Popped %d\n", delElem);
				else printf("Popping failed\n");
				break;
			case 3:
				if(peep(sp, &elem))
					printf("Top element: %d\n", elem);
				else printf("Peep operation failed\n");
				break;
			case 4:
				display(sp);
				break;
			case 5: 
				destroy(sp);
				return 0;
			default:
				printf("Invalid option: %d\n", option);
		}
	}

	
	printf("\n");
	return 0;
}
