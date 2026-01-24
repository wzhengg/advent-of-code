#include <stdio.h>
#include <stdlib.h>

#define N 8192
#define TRUE 1

char grid[N+N+1][N+N+1];

int main(void) {
	FILE *fp = fopen("input.txt", "r");
	if (fp == NULL) {
		exit(1);
	}

	char buf[N];
	if (fread(buf, sizeof(char), N, fp) != N) {
		exit(1);
	}

	fclose(fp);

	int r, c, rr, cc, count;

	r = c = rr = cc = N;
	count = 1;
	grid[r][c] = TRUE;

	for (int i = 0; i < N; ++i) {
		int *x = i%2==0 ? &r : &rr;
		int *y = i%2==0 ? &c : &cc;

		switch (buf[i]) {
			case '^':
				--(*x);
				break;
			case '>':
				++(*y);
				break;
			case 'v':
				++(*x);
				break;
			case '<':
				--(*y);
				break;
		}

		if (!grid[*x][*y]) {
			grid[*x][*y] = TRUE;
			++count;
		}
	}

	printf("%d\n", count);

	return 0;
}
