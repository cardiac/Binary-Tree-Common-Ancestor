CC=gcc
CFLAGS=-std=c11 -Wall -Wpedantic

SOURCE_DIR=src/
OBJECT_DIR=bin/

SOURCES := $(wildcard $(SOURCE_DIR)*.c)
OBJECTS := $(patsubst %.c,$(OBJECT_DIR)%,$(notdir $(SOURCES)))

all: $(OBJECTS)

$(OBJECT_DIR)%: $(SOURCE_DIR)%.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf bin/*
