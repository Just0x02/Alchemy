# THIS BUILD FILE IS ONLY FOR THE TESTS
# IT'S ALSO ONLY FOR WINDOWS USERS USING MSYS

export TMP=C:\msys64\tmp

CC = g++
CFLAGS = -Wall -Wno-unused-variable -Wno-narrowing -Wno-sign-compare
CSTD = -std=c++20

INCLUDES = -I ./include

SOURCEDIR = ./tests

CPP_MAIN = ./main.cpp
OUTFILE = ./main

CPP_SOURCES := $(shell find $(SOURCEDIR) -name '*.cpp')
C_SOURCES   := $(shell find $(SOURCEDIR) -name '*.c')


BUILD_DIST_PREREQ := clean build
 
build:
	$(CC) $(CPP_MAIN) $(CPP_SOURCES) $(C_SOURCES) $(INCLUDES) $(CSTD) $(CFLAGS) -o $(OUTFILE)

clean:
	rm -f $(OUTFILE)

dist: $(BUILD_DIST_PREREQ)

.PHONY: all tests clean

run: build
	$(OUTFILE)