CFLAGS =-std=gnu11 -Wall -Wextra -ldl
LDLIBS =-pthread -ldl

.PHONY: all clean

all: task1 system_allocator.so

clean:
	$(RM) task1 system_allocator.so

system_allocator.so: system_allocator.c
	$(CC) -shared -fPIC -Wall system_allocator.c -o system_allocator.so

system_allocator.o: my_memory.h
task1: task1.c