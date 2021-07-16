#include <stdio.h>

void hanoi(int n, char from, char middle, char to);

int cnt = 0;

int main()
{
	int n;
	printf("������ ������ �Է��Ͻÿ�:");
	scanf("%d", &n);

	hanoi(n, 'A', 'B', 'C');
	printf("�� �̵� Ƚ�� : %d", cnt);
	return 0;
}

void hanoi(int n, char from, char middle, char to)
{
	cnt++;
	if ( n == 1 )
	{
		printf("%d�� ������ %c���� %c�� �̵�\n", n, from, to);
		return;
	}
	hanoi(n - 1, from, to, middle);
	printf("%d�� ������ %c���� %c�� �̵�\n", n, from, to);
	hanoi(n - 1, middle, from, to);
}
