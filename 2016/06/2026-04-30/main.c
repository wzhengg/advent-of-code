#include <stdio.h>
#include <stdlib.h>

#define COLS 8
#define NALPHA 26

int main(void) {
	FILE *fp = fopen("input.txt", "r");
	if (!fp)
		exit(1);

	char line[COLS+2];
	int count[COLS][NALPHA] = {0};

	while (fgets(line, COLS+2, fp)) {
		for (int i = 0; i < COLS; ++i) {
			char c = line[i];
			++count[i][c-'a'];
		}
	}

	char out[COLS+1] = {0};

	for (int i = 0; i < COLS; ++i) {
		int least = 0;
		for (int j = 1; j < NALPHA; ++j) {
			if (count[i][j] < count[i][least]) {
				least = j;
			}
		}
		out[i] = least + 'a';
	}

	printf("%s", out);

	return 0;
}
