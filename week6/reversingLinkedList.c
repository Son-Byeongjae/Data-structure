#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FALSE 0
#define TRUE 1

typedef struct Node
{
	int data;
	struct Node* nextNode;
} Node;

typedef struct LinkedList
{
	int curCount;
	Node headNode;
}LinkedList;

typedef struct StackNode
{
	int data;
	struct StackNode* next;
} StackNode;

// Linked list 관련 함수
int addNode(LinkedList* pList, int pos, int data);
void showNode(LinkedList* pList);
void makeEmpty(LinkedList* pList);

// Stack 관련 함수
void pushLinkedStack(StackNode** top, int data);
StackNode* popLinkedStack(StackNode** top);
void deleteLinkedStack(StackNode** top);
int isEmpty(StackNode* top);

// 추가된 함수
void reverseList(LinkedList* pList, StackNode** top);

int main()
{
	int pos;
	LinkedList* linkedList = (LinkedList*)malloc(sizeof(LinkedList));
	linkedList->curCount = 0;
	linkedList->headNode.nextNode = NULL;

	StackNode* top = NULL;
	StackNode* pNode;

	//showNode(linkedList);
	addNode(linkedList, 0, 10);
	addNode(linkedList, 5, 100);
	addNode(linkedList, 1, 20);
	addNode(linkedList, 2, 30);
	addNode(linkedList, 1, 50);
	addNode(linkedList, 1, 70);
	addNode(linkedList, 1, 40);

	showNode(linkedList);

	reverseList(linkedList, &top);

	showNode(linkedList);

	//removeNode(linkedList, 1);
	//showNode(linkedList);

	//pos = findPos(linkedList, 30);
	//printf("The location of node with data '30': %d\n", pos);

	makeEmpty(linkedList);
	showNode(linkedList);
	return 0;
}


// Linked list 관련 함수 정의
int addNode(LinkedList* pList, int pos, int data)
{
	int i = 0;
	Node* pNewNode = NULL;
	Node* pTmpNode = NULL;
	if ( pList == NULL )
	{
		printf("addNode() error1 \n");
		return FALSE;
	}
	if ( pos < 0 || pos > pList->curCount )
	{
		printf("addNode() error2: 추가 범위 초과 \n");
		return FALSE;
	}

	pNewNode = (Node*)malloc(sizeof(Node));
	if ( !pNewNode )
	{
		printf("addNode() error3 \n");
		return FALSE;
	}

	pNewNode->data = data;
	pNewNode->nextNode = NULL;

	pTmpNode = &(pList->headNode);
	for ( i = 0; i < pos; i++ )
		pTmpNode = pTmpNode->nextNode;

	pNewNode->nextNode = pTmpNode->nextNode;
	pTmpNode->nextNode = pNewNode;
	pList->curCount++;
	return TRUE;
}

void showNode(LinkedList* pList)
{
	Node* pNode = NULL;

	if ( pList == NULL )
	{
		printf("showNode() error\n");
		return;
	}

	printf("현재 Node 개수 : %d \n", pList->curCount);
	pNode = pList->headNode.nextNode;

	while ( pNode != NULL )
	{
		printf("[%d]\n", pNode->data);
		pNode = pNode->nextNode;
	}
	printf("-----------------------\n");
}

void makeEmpty(LinkedList* pList)
{
	Node* pDummyNode = NULL, * pTmpNode = NULL;
	if ( pList != NULL )
	{
		pTmpNode = pList->headNode.nextNode;
		while ( pTmpNode != NULL )
		{
			pDummyNode = pTmpNode;
			pTmpNode = pTmpNode->nextNode;
			free(pDummyNode);
		}
		pList->headNode.nextNode = NULL;
	}
	pList->curCount = 0;
}

// Stack 관련 함수 정의
void pushLinkedStack(StackNode** top, int data)
{
	StackNode* pNode = NULL;

	//넣을 Stack Node를 할당하고 data값을 저장
	pNode = (StackNode*)malloc(sizeof(StackNode));
	pNode->data = data;
	pNode->next = NULL;

	//만일 Stack이 empty일 경우 바로 top으로 지정
	if ( isEmpty(*top) ) *top = pNode;
	//Stack에 node가 하나라도 있는 경우 이어주기.
	else
	{
		pNode->next = (*top);
		*top = pNode;
	}
}

StackNode* popLinkedStack(StackNode** top)
{
	StackNode* pNode = NULL;

	//Stack이 비어있는지 검사
	if ( isEmpty(*top) )
	{
		printf("stack is empty\n");
		return NULL;
	}
	//pNode에 top이 가리키는 Node를 지정하고 top은 그 다음 Node로 지정 
	pNode = (*top);
	(*top) = pNode->next;

	return pNode;
}

void deleteLinkedStack(StackNode** top)
{
	StackNode* pNode = NULL, * pDelNode = NULL;
	pNode = *top;

	while ( pNode != NULL )
	{
		pDelNode = pNode;
		pNode = pNode->next;
		free(pDelNode);
	}
	*top = NULL;
}

int isEmpty(StackNode* top)
{
	if ( top == NULL )
		return TRUE;
	else
		return FALSE;
}

// 추가된 함수 정의
void reverseList(LinkedList* pList, StackNode** top)
{
	Node* pNode = NULL;
	StackNode *sNode = NULL;

	printf("Reverse Linked List!\n");
	//Stack에 List 저장
	pNode = pList->headNode.nextNode;
	while ( pNode != NULL )
	{
		pushLinkedStack(top, pNode->data);
		pNode = pNode->nextNode;
	}
	makeEmpty(pList);

	//List에 Stack 저장
	while ( isEmpty(*top) == FALSE )
	{
		sNode = popLinkedStack(top);
		addNode(pList, pList->curCount, sNode->data);
	}
	deleteLinkedStack(top);
}