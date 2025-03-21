# 指定编译器
CC = gcc

# 指定C语言标准和编译选项
CFLAGS = -std=c99 -Wall -I ./AVL -g

# 定义源文件和目标文件
SRCS = AVL/avl.c tests/testavl.c
OBJS = AVL/avl.o tests/testavl.o
TEST_PROGRAM = testavl

MAIN_SRCS = AVL/avl.c main.c
MAIN_OBJS = AVL/avl.o main.o
RUN_PROGRAM = main

.PHONY: all test clean run

all: $(TEST_PROGRAM) $(RUN_PROGRAM)

test: $(TEST_PROGRAM)
	./$(TEST_PROGRAM)

$(TEST_PROGRAM): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

$(RUN_PROGRAM): $(MAIN_OBJS)
	$(CC) $(CFLAGS) -o $@ $^

AVL/avl.o: AVL/avl.c AVL/avl.h
	$(CC) $(CFLAGS) -c $< -o $@

tests/testavl.o: tests/testavl.c AVL/avl.h
	$(CC) $(CFLAGS) -c $< -o $@

main.o: main.c AVL/avl.h
	$(CC) $(CFLAGS) -c $< -o $@

run: $(RUN_PROGRAM)
	./$(RUN_PROGRAM)

clean:
	rm -f $(OBJS) $(TEST_PROGRAM) $(RUN_PROGRAM) main.o