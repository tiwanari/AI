CC=gcc
OBJS=main.o board.o uct.o
CFLAGS=-g -Wall
TARGET=main

all: $(TARGET)

$(TARGET): $(OBJS)
	gcc -o $@ $(OBJS)

clean:
	rm $(TARGET) *.o
