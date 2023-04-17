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

int linearSearch(int list[], int size, int key)
{
	for(int i=0; i<size; i++)
		if(list[i] == key)
			return i;
	return -1;
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
	
	display(list, size);
	
	int res = linearSearch(list, size, key);
	if(res == -1)
		printf("%d not in list.\n", key);
	else
		printf("%d is at index %d of list.\n", key, res);
		
	return 0;
}
