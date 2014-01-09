.PHONY: clean test
CC=gcc
OBJS=aco.o main.o util.o
CFLAGS=-Wall -O3
TARGET=aco


all: $(TARGET)

$(TARGET): $(OBJS)
	gcc -o $@ $(OBJS)

calc_rho: $(TARGET)
	cp $(TARGET) ../calc_rho/$(TARGET)
	cd ../calc_rho ; ./calc_rho.sh

calc_alpha: $(TARGET)
	cp $(TARGET) ../calc_alpha/$(TARGET)
	cd ../calc_alpha ; ./calc_alpha.sh

calc_beta: $(TARGET)
	cp $(TARGET) ../calc_beta/$(TARGET)
	cd ../calc_beta ; ./calc_beta.sh

clean:
	rm $(TARGET) $(TEST) *.o
