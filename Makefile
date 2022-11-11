export TMP=C:\msys64\tmp

CC = g++
CFLAGS = -Wall -Wno-unused-variable -lpthread -Wno-narrowing -Wno-sign-compare

INCLUDES = -I ./include

SOURCEDIR = ./tests

CPP_MAIN = ./main.cpp
OUTFILE = ./main

CPP_SOURCES := $(shell find $(SOURCEDIR) -name '*.cpp')
C_SOURCES   := $(shell find $(SOURCEDIR) -name '*.c')


BUILD_DIST_PREREQ := clean build
 
build:
	$(CC) $(CPP_MAIN) $(CPP_SOURCES) $(C_SOURCES) $(INCLUDES) $(CFLAGS) -o $(OUTFILE)

clean:
	rm -f $(OUTFILE)

dist: $(BUILD_DIST_PREREQ)

.PHONY: all tests clean

run: build
	$(OUTFILE)