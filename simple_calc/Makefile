TARGET = simple_calc
OBJS = simple_calc.o
SRCS = simple_calc.c
LIBRARY = libbinaty_op.a libstack_op.a

INCLUDES_DIR := \
	-I. 	\
	-I(../binary_tree/) 	\
	-I(../stack/)
LIBS_DIR := \
	-L. 	\
	-L(../binary_tree/) 	\
	-L(../stack/)

CFLAGS = -c $(INCLUDES_DIR)
LDFLAGS = $(LIBRARY)
CC = gcc

$(TARGET):$(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^
$(OBJS):$(SRCS)
	$(CC) $(CFLAGS) -o $@

clean:
	#rm -rf $(OBJS)

