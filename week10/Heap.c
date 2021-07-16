#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_NODES 50

typedef struct Heap
{
	int nodes[MAX_NODES];
	int lastIndex;
} Heap;

void initHeap(Heap* heap);
void insertData(Heap* heap, int data);
void printHeap(Heap heap);
void deleteData(Heap* heap);

int main() {
	Heap heap;
	initHeap(&heap);

	insertData(&heap, 1);
	insertData(&heap, 3);
	insertData(&heap, 8);
	insertData(&heap, 13);
	insertData(&heap, 4);
	insertData(&heap, 10);
	insertData(&heap, 6);

	printHeap(heap);

	deleteData(&heap);
	printHeap(heap);

	deleteData(&heap);
	printHeap(heap);

	return 0;
}


void initHeap(Heap* heap) {
	int i;
	for (i = 1; i < MAX_NODES; i++) {
		heap->nodes[i] = 0;
	}
	heap->lastIndex = 0;
}

void printHeap(Heap heap) {
	int i, count, newLineIndex;

	count = 1;
	newLineIndex = 0;

	for (i = 1; i <= heap.lastIndex; i++) {
		printf("%d\t", heap.nodes[i]);

		if (pow(2, newLineIndex) == count) {
			printf("\n");
			newLineIndex++;
			count = 0;
		}
		count++;
	}
	printf("\n\n");
}

void insertData(Heap* heap, int data) {
	int index;

	//heap이 꽉 차있는지 검사
	if (heap->lastIndex == MAX_NODES - 1) {
		printf("Heap is full\n");
		return;
	}

	//heap에 node를 확장시켜 데이터를 추가
	heap->lastIndex++;
	index = heap->lastIndex;

	//부모 node의 데이터를 확인하면서 업데이트
	while ( (index != 1) && (data > heap->nodes[index / 2]) )
	{
		heap->nodes[index] = heap->nodes[index / 2];
		index /= 2;
	}
	heap->nodes[index] = data;
}

void deleteData(Heap* heap) {
	int temp, parentIndex, childIndex;

	//heap이 비어있는지 검사
	if (heap->lastIndex == 0) {
		printf("Heap is empty\n");
		return;
	}

	//root node에만 데이터가 존재하는 경우
	if (heap->lastIndex == 1) {
		heap->nodes[heap->lastIndex] = 0;
		heap->lastIndex = 0;
		return;
	}

	//heap의 마지막 node의 데이터를 임시 변수에 저장
	temp = heap->nodes[heap->lastIndex];
	heap->nodes[heap->lastIndex] = 0;
	heap->lastIndex--;

	parentIndex = 1;
	childIndex = 2;

	//root node에서 시작하여 자식 노드의 값과 비교하며 업데이트
	while (childIndex <= heap->lastIndex) {
		//sibling node 중에서 값이 가장 큰 node를 선택
		if ( heap->nodes[childIndex] < heap->nodes[childIndex + 1] )
			childIndex++;

		//임시변수에 저장된 값과 비교
		if ( temp > heap->nodes[childIndex] )
			break;

		//자식 node의 값이 더 큰 경우에는 부모 node와 교체
		heap->nodes[parentIndex] = heap->nodes[childIndex];
		parentIndex = childIndex;
		childIndex *= 2;
	}
	heap->nodes[parentIndex] = temp;
}