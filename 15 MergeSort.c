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

void merge(int list[], int low, int mid, int high)
{
	const int tempSize = high - low + 1;
		
	// allocate memory for temp array
	int *temp = (int*)malloc(sizeof(int) * tempSize);
	
	// initialize indices
	int i = low, j = mid+1, k = 0;
	// as long as there are elements in both the sublists
	while(i <= mid && j <= high)
	{
		// put the smaller element of both the sublists into temp
		if(list[i] < list[j])
			temp[k++] = list[i++];
		else
			temp[k++] = list[j++];
	}
	
	// add any remaining elements to list
	while(i <= mid)
		temp[k++] = list[i++];
	while(j <= high)
		temp[k++] = list[j++];
		
	// copy all the elements from temp to original list
	for(int i=0; i<tempSize; i++)
		list[low + i] = temp[i];
	
	// release memory of temp array
	free(temp);
}

void mergeSort(int list[], int low, int high)
{
	int mid;
	if(low < high)
	{
		mid = (low+high)/2;
		mergeSort(list, low, mid);
		mergeSort(list, mid+1, high);
		merge(list, low, mid, high);
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
	
	mergeSort(list, 0, size-1);
	
	printf("After sorting:  ");
	display(list, size);
	
	return 0;
}
