#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

#include <assert.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

typedef uint8_t  u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef int8_t  i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

#define ABS(x) ((x) < 0 ? -(x) : (x))

typedef struct String String;
struct String {
	u8 *str;
	u64 len;
};

enum Direction { NORTH, SOUTH, EAST, WEST };
typedef enum Direction Direction;

typedef struct Position Position;
struct Position {
	Direction dir;
	i32 x;
	i32 y;
};

static Position pos = {.dir = NORTH, .x = 0, .y = 0};

void move(u8 turn, i32 n) {
	assert(turn == 'L' || turn == 'R');
	assert(pos.dir == NORTH || pos.dir == SOUTH || pos.dir == EAST || pos.dir == WEST);

	switch (pos.dir) {
		case NORTH:
			pos.dir = (turn == 'L') ? WEST : EAST;
			break;
		case SOUTH:
			pos.dir = (turn == 'L') ? EAST : WEST;
			break;
		case EAST:
			pos.dir = (turn == 'L') ? NORTH : SOUTH;
			break;
		case WEST:
			pos.dir = (turn == 'L') ? SOUTH : NORTH;
			break;
	}

	switch (pos.dir) {
		case NORTH:
			pos.x += n;
			break;
		case SOUTH:
			pos.x -= n;
			break;
		case EAST:
			pos.y += n;
			break;
		case WEST:
			pos.y -= n;
			break;
	}
}

String read_instruction(String input, u64 *offp) {
	if (*offp >= input.len) {
		return (String){0};
	}

	u8 *start = &input.str[*offp];

	while (*offp < input.len && input.str[*offp] != ',') {
		*offp += 1;
	}

	String ret = {.str = start, .len = &input.str[*offp] - start};

	*offp += 2;

	return ret;
}

int main(void) {
	int fd = open("input.txt", O_RDONLY);
	assert(fd != -1);

	struct stat stat;
	assert(fstat(fd, &stat) != -1);

	i32 filesize = stat.st_size;

	u8 *buf = mmap(NULL, filesize, PROT_READ|PROT_WRITE, MAP_ANONYMOUS|MAP_PRIVATE, -1, 0);
	assert(buf != MAP_FAILED);

	assert(read(fd, buf, filesize) == filesize);

	String input = {.str = buf, .len = filesize};
	u64 offset = 0;

	while (1) {
		String in = read_instruction(input, &offset);
		if (in.len == 0) {
			break;
		}

		i32 n = atol((char *)in.str + 1);
		move(*in.str, n);
	}

	printf("%d\n", ABS(pos.x) + ABS(pos.y));

	return 0;
}
