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

struct StackADT
{
	Node *tos;
};
typedef struct StackADT Stack;

Stack *create(void)
{
	// allocate memory for Stack
	Stack *pthis = (Stack *)malloc(sizeof(Stack));
	// initialize members
	pthis->tos = NULL;
	return pthis;	
}

int size(const Stack *pthis)
{
	int count = 0;
	Node *cursor = pthis->tos;
	while(cursor != NULL)
	{
		count++;
		cursor = cursor->link;
	}
	return count;
}

bool push(Stack *pthis, char data)
{
	// create new node with data
	Node *pNew = createNode(data);
	// insert new node prior to tos
	pNew->link = pthis->tos;
	// new node is the tos now
	pthis->tos = pNew;
	return true;
}

bool pop(Stack *pthis, char *pData)
{
	// check if Stack is empty
	if(pthis->tos == NULL)
		return false;
	// store data to pass by ref variable
	*pData = pthis->tos->data;
	// head is to be deleted
	Node *pDel = pthis->tos;
	// logical deletion
	pthis->tos = pDel->link;
	free(pDel); // physical deletion
	return true;
}

bool peep(Stack *pthis, char *pData)
{
	// check if Stack is empty
	if(pthis->tos == NULL)
		return false;
	// store data to pass by ref variable
	*pData = pthis->tos->data;
	return true;
}

void destroy(Stack *pthis)
{
	char temp;
	while(pthis->tos != NULL) // while list is not empty
		pop(pthis, &temp); // delete elements
	free(pthis); // free Stack
}

void display(const Stack *pthis)
{
	// start cursor at tos
	Node *cursor = pthis->tos;
	while(cursor != NULL) // loop till end of Stack
	{
		printf("%c\n", cursor->data);
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
	
	Stack *sp = create();
	
	while(true)
	{
		printf("\n1. Push\n2. Pop\n3. Peep\n4. Display\n5. Exit\n");
		printf("Select an option: ");
		scanf("%d", &option);
		getchar(); // get rid of a newline after entering option
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
					printf("Popped %c\n", delElem);
				else printf("Popping failed\n");
				break;
			case 3:
				if(peep(sp, &elem))
					printf("Top element: %c\n", elem);
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
