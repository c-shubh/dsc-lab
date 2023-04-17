#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>

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

int partition(int list[], int low, int high)
{
	// let the 1st elem be the pivot
	int pivot = list[low];
	int i = low;
	int j = high;
	
	while(i < j)
	{
		// place i to elem higher than pivot
		while(list[i] <= pivot)
			i++;
		// place j to elem lower than pivot
		while(list[j] > pivot)
			j--;
		
		// exchange ith and jth elements
		if(i < j)
			exchange(&list[i], &list[j]);
	}
	// control out of loop => i and j crossed each other
	// exchange pivot and jth element
	list[low] = list[j];
	list[j] = pivot;
	
	return j;
}

void quickSort(int list[], int low, int high)
{
	int j;
	if(low < high)
	{
		// partition the list
		j = partition(list, low, high);
		// apply quick sort to sublist [low..j-1]
		quickSort(list, low, j-1);
		// apply quick sort to sublist [j+1..high]
		quickSort(list, j+1, high);
	}
}

bool isSorted(int list[], int size)
{
	for(int i=0; i<size-1; i++)
		if(list[i] > list[i+1])
			return false;
	return true;
}

int main(int argc, char *argv[])
{
	if(argc <= 1)
	{
		puts("Usage: ./a.out size");
		return 1;
	}
	srand(time(NULL));
	int size = atoi(argv[1]);
	int *list = malloc(sizeof(int) * size);
	readList(list, size);
	quickSort(list, 0, size-1);
	if(isSorted(list, size))
		printf("Size: %d sorted.\n", size);
	else printf("Size: %d not sorted.\n", size);
	
	return 0;		
}

/*
int main(void)
{
	srand(time(NULL));

	const int size = 8;
	int list[size];
	
//	printf("Enter list: ");
	readList(list, size);
	
	printf("Before sorting: ");
	display(list, size);
	
	quickSort(list, 0, size-1);
	
	printf("After sorting:  ");
	display(list, size);
	
	return 0;
}
*/
