#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define LINES 1000
#define STRLEN 16

char lines[LINES][STRLEN+2];

bool isnice(char *s);

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
	int vowels = 0;
	for (int i = 0; i < STRLEN; ++i) {
		if (s[i] == 'a' || s[i] == 'e' || s[i] == 'i' || s[i] == 'o' || s[i] == 'u') {
			++vowels;
		}
	}
	if (vowels < 3) {
		return false;
	}

	for (int i = 0; i < STRLEN-1; ++i) {
		if (s[i] == 'a' && s[i+1] == 'b') return false;
		if (s[i] == 'c' && s[i+1] == 'd') return false;
		if (s[i] == 'p' && s[i+1] == 'q') return false;
		if (s[i] == 'x' && s[i+1] == 'y') return false;
	}

	for (int i = 0; i < STRLEN-1; ++i) {
		if (s[i] == s[i+1]) {
			return true;
		}
	}

	return false;
}
