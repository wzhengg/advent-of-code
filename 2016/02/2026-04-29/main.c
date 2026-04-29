#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>

#define DIGITS 5

char keypad[][5] = {
	{ 0 ,  0 , '1',  0 ,  0 },
	{ 0 , '2', '3', '4',  0 },
	{'5', '6', '7', '8', '9'},
	{ 0 , 'A', 'B', 'C',  0 },
	{ 0 ,  0 , 'D',  0 ,  0 }
};

int main(void) {
	FILE *fp = fopen("input.txt", "r");
	if (fp == NULL) {
		exit(1);
	}

	char *line = NULL;
	size_t n = 0;
	ssize_t nread;

	int row = 2;
	int col = 0;

	char code[DIGITS];
	int ci = 0;

	for (int i = 0; (nread = getline(&line, &n, fp)) != -1 && i < DIGITS; ++i) {
		for (int j = 0; j < nread-1; ++j) {
			switch (line[j]) {
				case 'U':
					--row;
					if (row < 0 || keypad[row][col] == 0)
						++row;
					break;
				case 'D':
					++row;
					if (row > 4 || keypad[row][col] == 0)
						--row;
					break;
				case 'L':
					--col;
					if (col < 0 || keypad[row][col] == 0)
						++col;
					break;
				case 'R':
					++col;
					if (col > 4 || keypad[row][col] == 0)
						--col;
					break;
			}
		}

		code[ci++] = keypad[row][col];
	}

	fwrite(code, sizeof(char), sizeof(code)/sizeof(char), stdout);

	return 0;
}
