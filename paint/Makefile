CC = gcc
CFLAGS = -Wall -I./include
SRCS = src/canvas.c src/command_history.c src/display.c src/result.c
MAIN_SRC = src/paintapp.c
OBJS = $(SRCS:.c=.o)
TARGET = bin/paintapp
LIB = lib/libpaint.a

all: $(TARGET)

$(TARGET): $(MAIN_SRC) $(LIB)
	$(CC) $(CFLAGS) -o $@ $< -L./lib -lpaint

$(LIB): $(OBJS)
	ar rsv $@ $^

src/%.o: src/%.c 
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJS) $(LIB) $(TARGET)
