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

void exchange(int *a, int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

void bubbleSort(int list[], int size)
{
	// perform size-1 passes
	for(int pass=1; pass<size; pass++)
		for(int i=0; i<size-pass; i++)
			// if current elem is greater than the next elem, exchange.
			if(list[i] > list[i+1])
				exchange(&list[i], &list[i+1]);
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
	
	bubbleSort(list, size);
	
	printf("After sorting:  ");
	display(list, size);
	
	return 0;
}
