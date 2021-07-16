#include <stdio.h>
#include <stdlib.h>

int list[7] = { 38,27,43,3,9,82,10 };

int partition(int list[], int left, int right)
{
	int pivot, temp;
	int low, high;

	low = left;
	high = right + 1;
	pivot = list[left];

	do
	{
		do
		{
			low++;
		}
		while ( low <= right && list[low] < pivot );
		do
		{
			high--;
		}
		while ( high >= left && list[high] > pivot );

		if ( low < high )
		{
			temp = list[low];
			list[low] = list[high];
			list[high] = temp;
		}
	}
	while ( low < high );

	temp = list[left];
	list[left] = list[high];
	list[high] = temp;

	return high;
}

void quickSort(int list[], int left, int right)
{
	if ( left < right )
	{
		int q = partition(list, left, right);
		quickSort(list, left, q - 1);
		quickSort(list, q + 1, right);
	}
}

int main()
{
	int i = 0;

	quickSort(list, 0, 6);

	for ( i = 0; i < 7; i++ )
		printf("%d\t", list[i]);

	printf("\n");

	return 0;
}