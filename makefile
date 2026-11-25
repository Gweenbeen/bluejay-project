# Copyright (c) 2026 Justin Wallace
# makefile - Make build script

CC := \
	clang

CFLAGS := \
	-g \
	-std=c23 \
	-I lib

SRC := \
	lib/main.c \
	lib/source/source_file.c \
	lib/lexer/lexer.c \
	lib/ast/ast.c \
	lib/bump_arena.c 


BUILD := \
	$(patsubst lib/%.c, build/%.o, $(SRC))

TARGET := \
	bin/bjcc.exe

all: $(TARGET)

$(TARGET): $(BUILD)
	$(CC) $(CFLAGS) $^ -o $@

build/%.o: lib/%.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: all