#include <stdio.h>

void hanoi(int n, char from, char middle, char to);

int cnt = 0;

int main()
{
	int n;
	printf("원판의 개수를 입력하시오:");
	scanf("%d", &n);

	hanoi(n, 'A', 'B', 'C');
	printf("총 이동 횟수 : %d", cnt);
	return 0;
}

void hanoi(int n, char from, char middle, char to)
{
	cnt++;
	if ( n == 1 )
	{
		printf("%d번 원판을 %c에서 %c로 이동\n", n, from, to);
		return;
	}
	hanoi(n - 1, from, to, middle);
	printf("%d번 원판을 %c에서 %c로 이동\n", n, from, to);
	hanoi(n - 1, middle, from, to);
}
