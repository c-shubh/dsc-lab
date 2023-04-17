#include <stdio.h>

void display(int list[], int size)
{
	printf("Index: ");
	for(int i=0; i<size; i++)
		printf("%d\t", i);
	printf("\nList:  ");
	for(int i=0; i<size; i++)
		printf("%d\t", list[i]);
	printf("\n");
}

void readList(int list[], int size)
{
	for(int i=0; i<size; i++)
		scanf("%d", &list[i]);
}

int iterativeBinarySearch(int list[], int size, int key)
{
	int low = 0;
	int high = size-1;
	int mid;
	
	while(low <= high)
	{
		mid = (low+high)/2;
		if(key == list[mid])
			return mid;
		else if(key > list[mid])
			low = mid + 1;
		else
			high = mid - 1;
	}
	return -1;
}

int recursiveBinarySearch(int list[], int low, int high, int key)
{
	if(low > high)
		return -1;
	
	int mid = (low+high)/2;
	if(key == list[mid])
		return mid;
	else if(key > list[mid])
		return recursiveBinarySearch(list, mid + 1, high, key);
	else
		return recursiveBinarySearch(list, low, mid - 1, key);

}

int main(void)
{
	int key;
	const int size = 8;
	int list[size];	

	printf("Enter list: ");
	readList(list, size);
	
	printf("Enter key: ");
	scanf("%d", &key);
	
	char choice;
	printf("Enter i for iterative binary search.\n");
	printf("      r for recursive binary search.\n");
	scanf(" %c", &choice);
	
	int res;
	display(list, size);
	switch(choice)
	{
		case 'i':
			res = iterativeBinarySearch(list, size, key);
			break;
		case 'r':
			res = recursiveBinarySearch(list, 0, size-1, key);
			break;
		default:
			printf("Invalid choice.\n");
			return 1;
	}
	
	if(res == -1)
		printf("%d not in list.\n", key);
	else
		printf("%d is at index %d of list.\n", key, res);
		
	return 0;
}
