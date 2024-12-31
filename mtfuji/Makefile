CC = gcc
CFLAGS = -Wall
LDLIBS = -lm
OBJS = mtfuji.o func.o optimize1.o
TARGET = mtfuji

$(TARGET): $(OBJS)
	$(CC) -o $@ $^ $(LDLIBS)

.PHONY: tmpclean clean
tmpclean:
	rm -f *~
clean: tmpclean
	rm -f $(OBJS) $(TARGET) 