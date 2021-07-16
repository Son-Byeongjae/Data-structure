#include <stdio.h>
#include <stdlib.h>

int list[7] = { 38,27,43,3,9,82,10 };

void merge(int list[], int left, int mid, int right)
{
	int i, j, k, l;
	i = left; j = mid + 1; k = left;
	int* temp = (int*)malloc(sizeof(int) * (7));

	while ( i <= mid && j <= right )
	{
		if ( list[i] <= list[j] )
			temp[k++] = list[i++];
		else
			temp[k++] = list[j++];
	}

	while ( i <= mid )
		temp[k++] = list[i++];
	while ( j <= right )
		temp[k++] = list[j++];

	for ( l = left; l <= right; l++ )
		list[l] = temp[l];
}

void mergeSort(int list[], int left, int right)
{
	int mid;
	if ( left < right )
	{
		mid = (left + right) / 2;
		mergeSort(list, left, mid);
		mergeSort(list, mid + 1, right);
		merge(list, left, mid, right);
	}
}

int main()
{
	int i = 0;

	mergeSort(list, 0, 6);
	for ( i = 0; i < 7; i++ )
		printf("%d\t", list[i]);

	printf("\n");

	return 0;
}