#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define N 99

#define MIN(x, y) ((x) < (y) ? (x) : (y))
#define MAX(x, y) ((x) > (y) ? (x) : (y))

long scenic_score(char grid[N][N+2], int row, int col) {
	long res = 1;

	int r, c;

	for (c = MAX(0, col-1); c > 0 && grid[row][c] < grid[row][col]; --c)
		;
	res *= (col-c);

	for (c = MIN(N-1, col+1); c < N-1 && grid[row][c] < grid[row][col]; ++c)
		;
	res *= (c-col);

	for (r = MAX(0, row-1); r > 0 && grid[r][col] < grid[row][col]; --r)
		;
	res *= (row-r);

	for (r = MIN(N-1, row+1); r < N-1 && grid[r][col] < grid[row][col]; ++r)
		;
	res *= (r-row);

	return res;
}

int main(void) {
	FILE *fp = fopen("input.txt", "r");
	if (!fp) exit(1);

	char grid[N][N+2];
	for (int i = 0; i < N; ++i)
		assert(fgets(grid[i], N+2, fp));

	int res = 0;
	for (int r = 0; r < N; ++r) {
		for (int c = 0; c < N; ++c) {
			long score = scenic_score(grid, r, c);
			if (score > res)
				res = score;
		}
	}

	printf("%d\n", res);

	return 0;
}
