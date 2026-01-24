#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define LINES 1000
#define STRLEN 16

char lines[LINES][STRLEN+2];

bool isnice(char *s);
bool has_double_pair(char *s);
bool has_sandwich(char *s);

int main(void) {
	FILE *fp = fopen("input.txt", "r");
	if (fp == NULL) {
		exit(1);
	}

	for (int i = 0; i < LINES; ++i) {
		if (fgets(lines[i], STRLEN+2, fp) == NULL) {
			exit(1);
		}
	}

	fclose(fp);

	int count = 0;
	for (int i = 0; i < LINES; ++i) {
		if (isnice(lines[i])) {
			++count;
		}
	}

	printf("%d\n", count);

	return 0;
}

bool isnice(char *s) {
	return has_double_pair(s) && has_sandwich(s);
}

bool has_double_pair(char *s) {
	for (int i = 0; i < STRLEN-1; ++i) {
		for (int j = i+2; j < STRLEN-1; ++j) {
			if (s[i] == s[j] && s[i+1] == s[j+1]) {
				return true;
			}
		}
	}

	return false;
}

bool has_sandwich(char *s) {
	for (int i = 0; i < STRLEN-2; ++i) {
		if (s[i] == s[i+2]) {
			return true;
		}
	}

	return false;
}
