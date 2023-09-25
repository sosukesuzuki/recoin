TEST_SRC_FILES := recoin.c test_recoin.c
EXECUTABLE_TEST := test_recoin
DEBUGGABLE_TEST := debug_test_recoin

CC := gcc
CFALGS := -Wall -Wextra -Werror -pedantic -std=c99 -O0

LLDB := lldb

CLANG_FORMAT := clang-format
FORMAT_FILES := $(wildcard *.c) $(wildcard *.h)

.PHONY: format run-test

$(EXECUTABLE_TEST): $(TEST_SRC_FILES)
	$(CC) $(CFLAGS) $(TEST_SRC_FILES) -o $(EXECUTABLE_TEST) -lm
$(DEBUGGABLE_TEST): $(TEST_SRC_FILES)
	$(CC) $(CFLAGS) $(TEST_SRC_FILES) -o $(EXECUTABLE_TEST) -lm -g

run-test: $(EXECUTABLE_TEST)
	./$(EXECUTABLE_TEST)

debug-test: $(EXECUTABLE_TEST)
	$(LLDB) ./$(EXECUTABLE_TEST)

format:
	$(CLANG_FORMAT) -i $(FORMAT_FILES)
