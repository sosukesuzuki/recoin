TEST_SRC_FILES := recoin.c test_recoin.c
EXECUTABLE_TEST := test_recoin

CC := gcc
CFALGS := -Wall -Wextra -Werror -pedantic -std=c99 -g -O0

CLANG_FORMAT := clang-format
FORMAT_FILES := $(wildcard *.c) $(wildcard *.h)

.PHONY: format run-test

$(EXECUTABLE_TEST): $(TEST_SRC_FILES)
	$(CC) $(CFLAGS) $(TEST_SRC_FILES) -o $(EXECUTABLE_TEST) -lm

run-test: $(EXECUTABLE_TEST)
	./$(EXECUTABLE_TEST)

format:
	$(CLANG_FORMAT) -i $(FORMAT_FILES)
