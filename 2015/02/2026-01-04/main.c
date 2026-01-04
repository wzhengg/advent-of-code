#include <stdio.h>

long get_surface_area(long l, long w, long h);
long get_area_of_smallest_side(long l, long w, long h);

int main(void) {
	FILE *fp = fopen("input.txt", "r");
	if (fp == NULL) {
		fprintf(stderr, "failed to open file\n");
		return 1;
	}

	long res = 0;

	long l, w, h;
	while (fscanf(fp, "%ldx%ldx%ld", &l, &w, &h) != EOF) {
		res += get_surface_area(l, w, h);
		res += get_area_of_smallest_side(l, w, h);
	}

	fclose(fp);

	printf("%ld\n", res);

	return 0;
}

long get_surface_area(long l, long w, long h) {
	return (2*l*w) + (2*w*h) + (2*h*l);
}

long get_area_of_smallest_side(long l, long w, long h) {
	long res = l * w;
	if (w * h < res) {
		res = w * h;
	}
	if (h * l < res) {
		res = h * l;
	}
	return res;
}
