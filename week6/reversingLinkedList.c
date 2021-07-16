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

// Linked list ���� �Լ�
int addNode(LinkedList* pList, int pos, int data);
void showNode(LinkedList* pList);
void makeEmpty(LinkedList* pList);

// Stack ���� �Լ�
void pushLinkedStack(StackNode** top, int data);
StackNode* popLinkedStack(StackNode** top);
void deleteLinkedStack(StackNode** top);
int isEmpty(StackNode* top);

// �߰��� �Լ�
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


// Linked list ���� �Լ� ����
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
		printf("addNode() error2: �߰� ���� �ʰ� \n");
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

	printf("���� Node ���� : %d \n", pList->curCount);
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

// Stack ���� �Լ� ����
void pushLinkedStack(StackNode** top, int data)
{
	StackNode* pNode = NULL;

	//���� Stack Node�� �Ҵ��ϰ� data���� ����
	pNode = (StackNode*)malloc(sizeof(StackNode));
	pNode->data = data;
	pNode->next = NULL;

	//���� Stack�� empty�� ��� �ٷ� top���� ����
	if ( isEmpty(*top) ) *top = pNode;
	//Stack�� node�� �ϳ��� �ִ� ��� �̾��ֱ�.
	else
	{
		pNode->next = (*top);
		*top = pNode;
	}
}

StackNode* popLinkedStack(StackNode** top)
{
	StackNode* pNode = NULL;

	//Stack�� ����ִ��� �˻�
	if ( isEmpty(*top) )
	{
		printf("stack is empty\n");
		return NULL;
	}
	//pNode�� top�� ����Ű�� Node�� �����ϰ� top�� �� ���� Node�� ���� 
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

// �߰��� �Լ� ����
void reverseList(LinkedList* pList, StackNode** top)
{
	Node* pNode = NULL;
	StackNode *sNode = NULL;

	printf("Reverse Linked List!\n");
	//Stack�� List ����
	pNode = pList->headNode.nextNode;
	while ( pNode != NULL )
	{
		pushLinkedStack(top, pNode->data);
		pNode = pNode->nextNode;
	}
	makeEmpty(pList);

	//List�� Stack ����
	while ( isEmpty(*top) == FALSE )
	{
		sNode = popLinkedStack(top);
		addNode(pList, pList->curCount, sNode->data);
	}
	deleteLinkedStack(top);
}