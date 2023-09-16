CLANG_FORMAT := clang-format
FORMAT_FILES := $(wildcard *.cpp) $(wildcard *.h)

.PHONY: format

format:
	$(CLANG_FORMAT) -i $(FORMAT_FILES)
