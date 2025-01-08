CC = gcc
CPPFLAGS = -I./include
CFLAGS = -Wall
LDLIBS = -lm
OBJS = src/adv_regression.o src/func.o src/optimize.o src/standerdization.o
TARGET = adv

bin/$(TARGET): $(OBJS)
	$(CC) $(CPPFLAGS) -o $@ $^ $(LDLIBS)

.PHONY: tmpclean clean
tmpclean:
	rm -f *~
clean: tmpclean
	rm -f $(OBJS) $(TARGET)