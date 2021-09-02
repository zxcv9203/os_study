#include <stdio.h>
#include <omp.h>

#define SIZE 100000000

int a[SIZE], b[SIZE], c[SIZE];

int main(int argc, char **argv)
{
	int i;
	
	for (i = 0; i < SIZE; i++)
		a[i] = b[i] = i;
	#pragma omp parallel for		// 아래의 for문을 병렬처리해줌
	for (i = 0; i < SIZE; i++) {
		c[i] = a[i] + b[i];
	}
	return 0;
}