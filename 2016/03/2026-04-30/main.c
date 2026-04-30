#include <stdio.h>
#include <stdlib.h>

#define MAXLINE 32

int main(void) {
	FILE *fp = fopen("input.txt", "r");
	if (fp == NULL) {
		exit(1);
	}

	char line[MAXLINE];
	int a, b, c;

	int res = 0;

	while (fgets(line, MAXLINE, fp) != NULL) {
		if (sscanf(line, "%d %d %d", &a, &b, &c) != 3) {
			exit(1);
		}

		if (a+b > c && b+c > a && a+c > b) {
			++res;
		}
	}

	printf("%d", res);

	return 0;
}
