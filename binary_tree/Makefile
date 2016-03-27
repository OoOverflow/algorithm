
TARGET = libbinary_tree_op.so
OBJ = binary_tree_op.o
SRC = binary_tree_op.c

CFLAGS := -c -fpic
CC = gcc

$(TARGET):$(SRC)
	$(CC) $(CFLAGS) -o $@ $^
clean:
	rm -rf $(OBJ)

