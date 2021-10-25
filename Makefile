CC = gcc
CFLAGS = -Wall

all: build build/output

build:
	mkdir build

build/output: build/main.o build/pbPlots.o build/supportLib.o
	$(CC) $(CFLAGS) $^ -o $@

build/main.o: src/main.c
	$(CC) $(CFLAGS) -c $< -o $@

build/pbPlots.o: src/external/pbPlots.c src/external/include/pbPlots.h
	$(CC) $(CFLAGS) -c $< -o $@

build/supportLib.o: src/external/supportLib.c src/external/include/supportLib.h
	$(CC) $(CFLAGS) -c $< -o $@