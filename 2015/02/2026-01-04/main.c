#include <stdio.h>

long get_volume(long l, long w, long h);
long get_smallest_perimeter(long l, long w, long h);

int main(void) {
	FILE *fp = fopen("input.txt", "r");
	if (fp == NULL) {
		fprintf(stderr, "failed to open file\n");
		return 1;
	}

	long res = 0;

	long l, w, h;
	while (fscanf(fp, "%ldx%ldx%ld", &l, &w, &h) != EOF) {
		res += get_volume(l, w, h);
		res += get_smallest_perimeter(l, w, h);
	}

	fclose(fp);

	printf("%ld\n", res);

	return 0;
}

long get_volume(long l, long w, long h) {
	return l * w * h;
}

long get_smallest_perimeter(long l, long w, long h) {
	long res = l+l+w+w;
	if (w+w+h+h < res) {
		res = w+w+h+h;
	}
	if (l+l+h+h < res) {
		res = l+l+h+h;
	}
	return res;
}
