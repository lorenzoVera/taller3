CC=g++
CFLAGS=-Wall -std=c++17
BINS=main ddskl.o
all: clean main

main: ddskl.o
	$(CC) $(CFLAGS) -o main main.cpp ddskl.o
ddskl.o: ddskl.cpp
	$(CC) $(CFLAGS) -c ddskl.cpp

clean:
	@echo " [CLN] Removing binary files"
	@rm -f $(BINS)