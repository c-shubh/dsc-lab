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

int findMaxElemIdx(int list[], int size)
{
	// assume 0th index elem to be the max
	int maxIdx = 0;
	for(int i=0; i<=size; i++)
		// if ith elem is greater than assumed max, update maxIdx
		if(list[i] > list[maxIdx])
			maxIdx = i;
	return maxIdx;
}

void selectionSort(int list[], int size)
{
	int maxIdx;
	// perform size-1 passes
	for(int pass=1; pass<size; pass++)
	{
		maxIdx = findMaxElemIdx(list, size-pass);	
		exchange(&list[maxIdx], &list[size-pass]);
	}
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
	
	selectionSort(list, size);
	
	printf("After sorting:  ");
	display(list, size);
	
	return 0;
}
