#include <stdio.h>
#include <time.h>
#include <stdlib.h>

void display(int list[], int size)
{
	printf("[ ");
	for(int i=0; i<size; i++)
		printf("%d ", list[i]);
	printf("]\n");
}

void readList(int list[], int size)
{
	for(int i=0; i<size; i++)
		list[i] = rand() % 100;
//		scanf("%d", &list[i]);
}

void insert(int list[], int size, int elem)
{
	int i;
	// place elem in already sorted sublist
	for(i=size-1; i>=0; i--)
		if(list[i] > elem)
			list[i+1] = list[i];
		else break;
	// place elem at correct position
	list[i+1] = elem;
}

void insertionSort(int list[], int size)
{
	int elem;
	// perform size-1 passes
	for(int pass=1; pass<size; pass++)
		insert(list, pass, list[pass]);
}

int main(void)
{
	srand(time(NULL));

	const int size = 8;
	int list[size];
	
//	printf("Enter list: ");
	readList(list, size);
	
	printf("Before sorting: ");
	display(list, size);
	
	insertionSort(list, size);
	
	printf("After sorting:  ");
	display(list, size);
	
	return 0;
}
