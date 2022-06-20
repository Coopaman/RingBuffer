#ifndef _RINGBUFFER_H

#include <stdint.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

typedef struct ringbuffer {
	// implement ringbuffer handle struct here
  uint32_t *buffer; //data buffer
  uint32_t head; //head pointer
  uint32_t tail; //tail pointer
  uint32_t bufferMax; //maximum size of the buffer
} ringbuffer_t;

typedef ringbuffer_t *ringbuffer_h;

ringbuffer_h ringbuffer_init(int size);
int ringbuffer_push(ringbuffer_h ring, int32_t value);
int ringbuffer_pop(ringbuffer_h ring, int32_t *value);
int ringbuffer_empty(ringbuffer_h ring);
int ringbuffer_full(ringbuffer_h ring);
int ringbuffer_remaining(ringbuffer_h ring);
int ringbuffer_destroy(ringbuffer_h);

#endif
