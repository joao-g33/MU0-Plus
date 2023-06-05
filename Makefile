CC = gcc

all:
	gcc vm.c -o vm -Wextra

.PHONY: clean
clean:
	rm -r vm
