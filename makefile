# Copyright (c) 2026 Justin Wallace
# makefile - Make build script

CC := \
	clang

CFLAGS := \
	-g \
	-std=c23 \
	-I lib

LIB := \
	lib/main.c \
	lib/array.c \
	

BUILD := \
	$(patsubst lib/%.c, build/%.o, $(LIB))

TARGET := \
	bin/bjcc.exe

all: $(TARGET)

$(TARGET): $(BUILD)
	$(CC) $(CFLAGS) $^ -o $@

build/%.o: lib/%.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: all