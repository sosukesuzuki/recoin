CLANG_FORMAT := clang-format
FORMAT_FILES := $(wildcard *.c) $(wildcard *.h)

.PHONY: format

format:
	$(CLANG_FORMAT) -i $(FORMAT_FILES)
