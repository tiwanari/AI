.PHONY: clean test
CC=gcc
OBJS=aco.o main.o util.o
CFLAGS=-Wall -O3
LFLAGS=-lm
TARGET=aco


all: $(TARGET)

$(TARGET): $(OBJS)
	gcc -o $@ $(OBJS) $(LFLAGS)

clean:
	rm $(TARGET) $(TEST) *.o
