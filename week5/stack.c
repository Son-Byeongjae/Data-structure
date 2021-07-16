#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0

//stack구조체 선언 (linked list)
typedef struct StackNode {
	int data;
	struct StackNode* next;
} StackNode;

//stack관련 함수
void pushLinkedStack(StackNode** top, int data);
StackNode* popLinkedStack(StackNode** top);
StackNode* topLinkedStack(StackNode* top);
void deleteLinkedStack(StackNode** top);

int isEmpty(StackNode* top) {
	if (top == NULL)
		return TRUE;
	else
		return FALSE;
}

void showLInkedStack(StackNode* top) {
	StackNode* pNode = NULL;
	if (isEmpty(top)) {
		printf("the stack is empty\n");
		return;
	}

	pNode = top;
	printf("==============Show Stack===============\n");
	while (pNode != NULL) {
		printf("[%d]\n", pNode->data);
		pNode = pNode->next;
	}
	printf("=======================================\n");
}

int main() {
	//가장 윗 부분을 가리키는 top 포인터 선언

	StackNode* top = NULL;
	StackNode* pNode;

	printf("Push 10, 20, 30 called.\n");
	pushLinkedStack(&top, 10);
	pushLinkedStack(&top, 20);
	pushLinkedStack(&top, 30);
	showLInkedStack(top);

	printf("Pop() called.\n");
	pNode = popLinkedStack(&top);
	if (pNode) {
		free(pNode);
		showLInkedStack(top);
	}

	printf("Top() called.\n");
	pNode = topLinkedStack(top);
	if (pNode)
		printf("Top node's data: %d\n", pNode->data);
	else
		printf("The stack is empty.\n");
	showLInkedStack(top);

	deleteLinkedStack(&top);

	return 0;
}

void pushLinkedStack(StackNode** top, int data)
{
	StackNode* pNode = NULL;

	//넣을 Stack Node를 할당하고 data값을 저장
	pNode = (StackNode*)malloc(sizeof(StackNode));
	pNode->data = data;
	pNode->next = NULL;

	//만일 Stack이 empty일 경우 바로 top으로 지정
	if ( isEmpty(*top) ) (*top) = pNode;
	//Stack에 node가 하나라도 있는 경우 이어주기.
	else
	{
		pNode->next = (*top);
		(*top) = pNode;
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

StackNode* topLinkedStack(StackNode* top)
{
	StackNode* pNode = NULL;

	if ( !isEmpty(top) )
		pNode = top;
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