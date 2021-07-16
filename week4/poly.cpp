#define _CRT_SECURE_NO_WARNINGS
#include "stdlib.h"
#include "stdio.h"
#include "string.h"

#define TESTCASE_FILE_NAME "testCases_poly.txt"
#define BUFFSIZE 1024

typedef struct polyTerm_
{
	int exp;
	int coeff;
	polyTerm_* next;
}polyTerm;

typedef struct poly_
{
	polyTerm* head;
}poly;

void clearPoly(poly* A)
{
	polyTerm* pTmpTerm = NULL;
	polyTerm* pDummyTerm = NULL;
	if ( A != NULL )
	{
		pTmpTerm = A->head;
		while ( pTmpTerm != NULL )
		{
			pDummyTerm = pTmpTerm;
			pTmpTerm = pTmpTerm->next;
			free(pDummyTerm);
		}
		A->head = NULL;
	}
}

poly createPoly(void)
{
	poly res;
	res.head = NULL;
	return res;
}

void addTerm(poly* A, int exp, int coeff)
{
	if ( coeff == 0 ) return;

	polyTerm* pNewTerm = (polyTerm*)malloc(sizeof(polyTerm));
	pNewTerm->exp = exp;
	pNewTerm->coeff = coeff;
	pNewTerm->next = NULL;

	if ( A->head == NULL ) 
	{
		A->head = pNewTerm;
	}
	else if ( A->head->exp < exp )
	{
		pNewTerm->next = A->head;
		A->head = pNewTerm;
	}
	else if ( A->head->exp == exp )
	{
		A->head->coeff += coeff;
		if ( A->head->coeff == 0 )
		{
			polyTerm* DelTerm = A->head;
			A->head = DelTerm->next;
			free(DelTerm);
			free(pNewTerm);
		}
	}
	else
	{
		polyTerm* pTmpTerm = (A->head);
		bool check = false;

		while ( pTmpTerm->next != NULL )
		{
			if ( pTmpTerm->next->exp == exp )
			{
				check = true;
				break;
			}
			else if ( pTmpTerm->next->exp < exp )
				break;
			pTmpTerm = pTmpTerm->next;
		}

		if ( check == true )
		{
			pTmpTerm->next->coeff += coeff;
			if ( pTmpTerm->next->coeff == 0 )
			{
				polyTerm* pDelTerm = pTmpTerm->next;
				pTmpTerm->next = pDelTerm->next;
				free(pDelTerm);
				free(pNewTerm);
			}
		}
		else
		{
			pNewTerm->next = pTmpTerm->next;
			pTmpTerm->next = pNewTerm;
		}
	}
}

poly multiPoly(poly A, poly B)
{
	poly res;
	res.head = NULL;
	
	if ( A.head == NULL || B.head == NULL )
		return res; 
	
	polyTerm* pTmpTerm1 = A.head;
	while ( pTmpTerm1 != NULL )
	{
		polyTerm* pTmpTerm2 = B.head;
		while ( pTmpTerm2 != NULL )
		{
			addTerm(&res, pTmpTerm1->exp + pTmpTerm2->exp, pTmpTerm1->coeff * pTmpTerm2->coeff);
			pTmpTerm2 = pTmpTerm2->next;
		}
		pTmpTerm1 = pTmpTerm1->next;
	}
	return res;
}

void printPoly_impl(poly A, char* buffer)
{
	if ( A.head == NULL )
	{
		sprintf(buffer, "0");
		return;
	}

	bool isFirst = true;
	char buffTemp[BUFFSIZE] = "";
	polyTerm* pTmpTerm = A.head;
	while ( pTmpTerm != NULL )
	{
		if ( isFirst || pTmpTerm->coeff < 0 )
		{
			sprintf(buffTemp, "%dx^%d", pTmpTerm->coeff, pTmpTerm->exp);
			strcat(buffer, buffTemp);
			isFirst = false;
			pTmpTerm = pTmpTerm->next;
		}
		else if ( pTmpTerm->coeff > 0 )
		{
			sprintf(buffTemp, "+%dx^%d", pTmpTerm->coeff, pTmpTerm->exp);
			strcat(buffer, buffTemp);
			pTmpTerm = pTmpTerm->next;
		}
	}
}

void printPoly(poly A)
{
	char buffer[BUFFSIZE] = "";
	printPoly_impl(A, buffer);
	printf(buffer);
}

void testPoly(const char* testCaseFileName)
{
	int breakFlag = 0;
	int breakPoint = -1;
	FILE* fp = fopen(testCaseFileName, "r");
	poly A = createPoly();
	poly B = createPoly();

	int T;
	fscanf(fp, "%d\n", &T);

	char lastTrue[BUFFSIZE] = "";
	char lastAnswer[BUFFSIZE] = "";

	while ( T-- )
	{
		char inputOp0, inputOp1;
		char inputStr[BUFFSIZE] = "";
		char buffer[BUFFSIZE] = "";
		int caseNum;

		fscanf(fp, "%d %c ", &caseNum, &inputOp0);

		if ( inputOp0 == 'a' )
		{
			int exp, coeff;
			fscanf(fp, "%c %d %d\n", &inputOp1, &exp, &coeff);
			if ( inputOp1 == 'A' )
			{
				addTerm(&A, exp, coeff);
			}
			else if ( inputOp1 == 'B' )
			{
				addTerm(&B, exp, coeff);
			}
		}

		else if ( inputOp0 == 'p' )
		{
			fscanf(fp, "%c\n%s\n", &inputOp1, inputStr);
			if ( inputOp1 == 'A' )
			{
				printPoly_impl(A, buffer);
			}
			else if ( inputOp1 == 'B' )
			{
				printPoly_impl(B, buffer);
			}

			if ( strcmp(inputStr, buffer) != 0 )
			{
				breakFlag = 1;
				breakPoint = caseNum;
				strcpy(lastTrue, inputStr);
				strcpy(lastAnswer, buffer);
				break;
			}
		}

		else if ( inputOp0 == 'c' )
		{
			fscanf(fp, "%c\n", &inputOp1);
			if ( inputOp1 == 'A' )
			{
				clearPoly(&A);
			}
			else if ( inputOp1 == 'B' )
			{
				clearPoly(&B);
			}
		}

		else if ( inputOp0 == 'm' )
		{
			fscanf(fp, "%s\n", inputStr);
			printPoly_impl(multiPoly(A, B), buffer);
			if ( strcmp(inputStr, buffer) != 0 )
			{
				breakFlag = 1;
				breakPoint = caseNum;
				strcpy(lastTrue, inputStr);
				strcpy(lastAnswer, buffer);
				break;
			}
		}
	}

	fclose(fp);

	if ( breakFlag )
	{
		printf("Test failed on case# %d\n", breakPoint);
		printf("True: %s\nAnswer: %s", lastTrue, lastAnswer);
	}
	else
	{
		printf("TEST DONE.\n");
	}
}

int main()
{
	testPoly(TESTCASE_FILE_NAME);
	return 0;
}
