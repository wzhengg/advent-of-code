#define _GNU_SOURCE
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define MIN(x, y) ((x) < (y) ? (x) : (y))
#define MAX(x, y) ((x) > (y) ? (x) : (y))

char keypad[][3] = {
	{'1', '2', '3'},
	{'4', '5', '6'},
	{'7', '8', '9'}
};

int main(void) {
	FILE *fp = fopen("input.txt", "r");
	if (fp == NULL) {
		exit(1);
	}

	char *line = NULL;
	size_t n = 0;
	ssize_t nread;

	int row = 1;
	int col = 1;

	char code[5];
	int ci = 0;

	while ((nread = getline(&line, &n, fp)) != -1) {
		for (int i = 0; i < nread-1; ++i) {
			switch (line[i]) {
				case 'U':
					row = MAX(0, row-1);
					break;
				case 'D':
					row = MIN(2, row+1);
					break;
				case 'L':
					col = MAX(0, col-1);
					break;
				case 'R':
					col = MIN(2, col+1);
					break;
				default:
					assert(0);
			}
		}

		code[ci++] = keypad[row][col];
	}

	fwrite(code, sizeof(char), sizeof(code)/sizeof(char), stdout);

	return 0;
}
