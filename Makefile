CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -Werror -O2 -g

TARGET = dab

SRCS = src/main.c src/builtins.CC
OBJS = (SRCS:.c=.o)


$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -f $(TARGET) $(OBJS)