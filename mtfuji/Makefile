CC = gcc
CPPFLAGS = -I./include
CFLAGS = -Wall
LDLIBS = -lm
OBJS = src/mtfuji.o src/func.o src/optimize1.o
TARGET = mtfuji

bin/$(TARGET): $(OBJS)
	$(CC) $(CPPFLAGS) -o $@ $^ $(LDLIBS)

.PHONY: tmpclean clean
tmpclean:
	rm -f *~
clean: tmpclean
	rm -f $(OBJS) $(TARGET) 