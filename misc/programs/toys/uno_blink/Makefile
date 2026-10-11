CC = gcc
CFLAGS = -Wall -Wextra -I../../../../include
LDFLAGS = -llapin
all: uno_blink
uno_blink: main.c
	$(CC) $(CFLAGS) main.c -o $@ $(LDFLAGS)
clean:
	rm -f uno_blink
.PHONY: all clean
