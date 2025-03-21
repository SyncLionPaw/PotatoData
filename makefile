# 指定编译器
CC = gcc

# 指定C语言标准
CFLAGS = -std=c99 -Wall -Wextra -I ./AVL

# 定义源文件和目标文件
SRCS = AVL/avl.c tests/testavl.c
OBJS = AVL/avl.o tests/testavl.o
TEST_PROGRAM = testavl

.PHONY: all test clean

all: $(TEST_PROGRAM)

test: $(TEST_PROGRAM)
	./$(TEST_PROGRAM)

$(TEST_PROGRAM): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

AVL/avl.o: AVL/avl.c AVL/avl.h
	$(CC) $(CFLAGS) -c $< -o $@

tests/testavl.o: tests/testavl.c AVL/avl.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TEST_PROGRAM)