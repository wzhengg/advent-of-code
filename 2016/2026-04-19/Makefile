BUILD := debug
STD   := c99

ifeq ($(BUILD),release)
	CFLAGS := -O2 -Wall -Wextra -Werror -pedantic
else
	CFLAGS := -O0 -g -Wall -Wextra -pedantic
endif

main: main.c
	gcc -o main main.c $(CFLAGS) -std=$(STD)

clean:
	rm main
