
build: ringbuffer_test

ringbuffer_test: test.c ringbuffer.c
	gcc -Werror -Wall test.c ringbuffer.c -o ringbuffer_test

test: ringbuffer_test
	./ringbuffer_test
