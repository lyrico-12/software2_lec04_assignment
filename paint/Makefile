CC = gcc
CPPFLAGS = -I./include
SRCS = src/canvas.c src/command_history.c src/display.c src/result.c
OBJS = $(SRCS:.c=.o)
EXEC = paint

%.o: %.c
    $(CC) $(CPPFLAGS) -c $< -o $@

.PHONY: clean
clean:
    rm -f $(OBJS) src/*.o $(EXEC) lib/*.a