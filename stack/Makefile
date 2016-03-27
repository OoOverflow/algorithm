
TARGET = libstack_op.so
OBJ = stack_op.o
SRC = stack_op.c

CFLAGS := -c -fpic
CC = gcc

$(TARGET):$(SRC)
	$(CC) $(CFLAGS) -o $@ $^
clean:
	rm -rf $(OBJ)

