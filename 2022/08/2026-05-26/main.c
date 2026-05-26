#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define N 99

int visible_left(char grid[N][N+2], int row, int col) {
	for (int c = 0; c < col; ++c)
		if (grid[row][c] >= grid[row][col])
			return 0;
	return 1;
}

int visible_right(char grid[N][N+2], int row, int col) {
	for (int c = col+1; c < N; ++c)
		if (grid[row][c] >= grid[row][col])
			return 0;
	return 1;
}

int visible_top(char grid[N][N+2], int row, int col) {
	for (int r = 0; r < row; ++r)
		if (grid[r][col] >= grid[row][col])
			return 0;
	return 1;
}

int visible_bot(char grid[N][N+2], int row, int col) {
	for (int r = row+1; r < N; ++r)
		if (grid[r][col] >= grid[row][col])
			return 0;
	return 1;
}

int is_visible(char grid[N][N+2], int r, int c) {
	return visible_left(grid, r, c) || visible_right(grid, r, c) || visible_top(grid, r, c) || visible_bot(grid, r, c);
}

int main(void) {
	FILE *fp = fopen("input.txt", "r");
	if (!fp) exit(1);

	char grid[N][N+2];
	for (int i = 0; i < N; ++i)
		assert(fgets(grid[i], N+2, fp));

	int res = 0;
	for (int r = 0; r < N; ++r)
		for (int c = 0; c < N; ++c)
			if (is_visible(grid, r, c))
				++res;

	printf("%d\n", res);

	return 0;
}
