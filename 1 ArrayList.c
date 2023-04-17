#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef float Type;

struct ArrayListADT
{
	Type *list;
	int size;
	int capacity;
};

typedef struct ArrayListADT ArrayList;

// Utility functions
void shiftToRight_(ArrayList *, int);
void shiftToLeft_(ArrayList *, int);
void swap_(Type *, Type *);

// ArrayList methods
ArrayList *create(int cap);
void destroy(ArrayList *);
bool insertBeg(ArrayList *, Type);
bool insertAt(ArrayList *, int , Type);
bool append(ArrayList *, Type);
bool deleteBeg(ArrayList *, Type *pDel);
bool deleteAt(ArrayList *, int, Type *);
bool deleteEnd(ArrayList *, Type *pDel);
void reverse(ArrayList *);
void display(const ArrayList *);

// Helper functions
void inputIndex(int *);
void inputElement(Type *);
void insertionErrorCheck(bool, Type);
void deletionErrorCheck(bool, Type *);

int main(void)
{
	int option, capacity, index;
	Type elem, deletedElem;
	bool res;
	
	printf("Enter array capacity: ");
	scanf("%d", &capacity);
	
	ArrayList *al = create(capacity);
	
	while(true)
	{
		printf("\n1. Insert\n2. Delete\n3. Reverse\n4. Display\n5. Exit\n");
		printf("Select an option: ");
		scanf("%d", &option);
		printf("\n");
		
		switch(option)
		{
			case 1: // insert
				inputElement(&elem);
				inputIndex(&index);
				if(index == 0)
					res = insertBeg(al, elem);
				else if(index == al->size-1)
					res = append(al, elem);
				else 
					res = insertAt(al, index, elem);
				insertionErrorCheck(res, elem);
				break;
			case 2: // delete
				inputIndex(&index);
				if(index == 0)
					res = deleteBeg(al, &deletedElem);
				else if(index == al->size-1)
					res = deleteEnd(al, &deletedElem);
				else 
					res = deleteAt(al, index, &deletedElem);
				deletionErrorCheck(res, &deletedElem);
				break;
			case 3: // reverse
				reverse(al);
				break;
			case 4: // display
				display(al);
				break;
			case 5: // exit
				destroy(al);
				return 0;
			default:
				printf("Invalid option: %d\n", option);
		}
	}

	
	printf("\n");
	return 0;
}

/* Helper functions */

void inputIndex(int *index)
{
	printf("Enter index: ");
	scanf("%d", index);
}

void inputElement(Type *elem)
{
	printf("Enter element to insert: ");
	scanf("%f", elem);
}

void insertionErrorCheck(bool inserted, Type elem)
{
	if(!inserted)
		printf("Error inserting %.3f: Array may be full.\n", elem);
}

void deletionErrorCheck(bool deleted, Type *pDel)
{
	if(!deleted)
		printf("Error deleting.\n");
	else
		printf("Deleted %.3f\n", *pDel);
}

/* Utility functions */

void shiftToRight_(ArrayList *pthis, int index)
{
	// shift elements from [size-1...index] to right by one position
	for(int i = pthis->size-1; i>=index; i--)
		pthis->list[i+1] = pthis->list[i];
}

void shiftToLeft_(ArrayList *pthis, int index)
{
	// shift elements from [index...size-1] to left by one position
	for(int i=index; i<pthis->size; i++)
		pthis->list[i] = pthis->list[i+1];
}

void swap_(Type *a, Type *b)
{
	Type temp = *a;
	*a = *b;
	*b = temp;
}

/* ArrayList methods */

ArrayList *create(int cap)
{
	// allocate memory for ArrayList (whole)
	ArrayList *pthis;
	pthis = (ArrayList *)malloc(sizeof(ArrayList));
	
	// initiaize members
	pthis->size = 0;
	pthis->capacity = cap;
	
	// allocate memory for list (part)
	pthis->list = malloc(cap * sizeof(Type));
	
	return pthis;
}

void destroy(ArrayList *pthis)
{
	// free list (part) and ArrayList (whole)
	free(pthis->list);
	free(pthis);
}

bool insertBeg(ArrayList *pthis, Type elem)
{
	// check array full
	if(pthis->size == pthis->capacity)
		return false;
	
	// shift elements to make space for new element
	shiftToRight_(pthis, 0);
	
	// add the element
	pthis->list[0] = elem;
	
	// increment the size
	pthis->size++;
	
	return true;
}

bool insertAt(ArrayList *pthis, int index, Type elem)
{
	// check array full
	if(pthis->size == pthis->capacity)
		return false;
	
	// bounds check
	if(index < 0 || index >= pthis->size)
		return false;
	
	if(index == 0)
		insertBeg(pthis, elem);
	else
	{
		// shift elements to make space for new element
		shiftToRight_(pthis, index);
		
		// add the element
		pthis->list[index] = elem;
	}
	
	// increment the size
	pthis->size++;
	return true;
}

bool append(ArrayList *pthis, Type elem)
{
	// check array full
	if(pthis->size == pthis->capacity)
		return false;
	
	// last position is size, new element
	pthis->list[pthis->size] = elem;
	
	// increment the size
	pthis->size++;
	
	return true; 
}

bool deleteBeg(ArrayList *pthis, Type *pDel)
{
	// check array empty
	if(pthis->size == 0)
		return false;
		
	// save data to be deleted
	*pDel = pthis->list[0];
	
	// overwrite element to be deleted
	shiftToLeft_(pthis, 0);
	
	// decrement the size
	pthis->size--;
	return true;
}

bool deleteAt(ArrayList *pthis, int index, Type *pDel)
{
	// check array empty
	if(pthis->size == 0)
		return false;
		
	// bounds check
	if(index < 0 || index >= pthis->size)
		return false;
		
	// save data to be deleted
	*pDel = pthis->list[index];
	
	// overwrite element to be deleted
	shiftToLeft_(pthis, index);
	
	// decrement the size
	pthis->size--;
	return true;
}

bool deleteEnd(ArrayList *pthis, Type *pDel)
{
	// check array empty
	if(pthis->size == 0)
		return false;
		
	// save data to be deleted
	*pDel = pthis->list[pthis->size-1];
	
	// decrement the size
	pthis->size--;
	return true;
}

void reverse(ArrayList *pthis)
{
	for(int i=0; i<pthis->size/2; i++)
		swap_(&pthis->list[i], &pthis->list[pthis->size - i - 1]);
}

void display(const ArrayList *pthis)
{
	printf("[ ");
	for(int i=0; i<pthis->size; i++)
		printf("%.3f ", pthis->list[i]);
	printf("]\n");
}

