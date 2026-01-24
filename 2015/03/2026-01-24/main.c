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

	int r, c, count;

	r = c = N;
	count = 1;
	grid[r][c] = TRUE;

	for (int i = 0; i < N; ++i) {
		switch (buf[i]) {
			case '^':
				--r;
				break;
			case '>':
				++c;
				break;
			case 'v':
				++r;
				break;
			case '<':
				--c;
				break;
		}

		if (!grid[r][c]) {
			grid[r][c] = TRUE;
			++count;
		}
	}

	printf("%d\n", count);

	return 0;
}
