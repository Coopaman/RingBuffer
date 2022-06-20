#include <stdio.h>
#include <stdint.h>
#include "ringbuffer.h"

/* Ringbuffer test file
 *
 * Implement any tests you want in here, and call them from main
 */
void FillBuffer(ringbuffer_h ring)
{
	//Hard Coded to push 9 values onto buffer
	ringbuffer_push(ring,1);
	ringbuffer_push(ring,20);
	ringbuffer_push(ring,12);
	ringbuffer_push(ring,5);
	ringbuffer_push(ring,78);
	ringbuffer_push(ring,22);
	ringbuffer_push(ring,94);
	ringbuffer_push(ring,68);
	ringbuffer_push(ring,24);

}

void getRingInfo(ringbuffer_h ring)
{
	//gets infromation about the ringbuffer
	printf("Head Position :%d\n",ring->head);
	printf("Tail Position :%d\n",ring->tail);
	printf("Buffer Size :%d\n",ring->bufferMax);

}


void getValues(ringbuffer_h ring)
{
	//gets the values in the slots of the ringbuffer
	int i;
	for(i = 0; i < ring->bufferMax; i++)
	{
		printf("Slot %d :%d\n",i,ring->buffer[i]);

	}

}

int smoketest() {
	ringbuffer_h ring;
	int32_t value;

	ring = ringbuffer_init(10);
	if (ring == NULL) {
		printf("ringbuffer_init returned null\n");
		return 1;
	}

	if (ringbuffer_push(ring, 1)) {
		printf("ringbuffer_push returned unsuccessful\n");
		return 1;
	}

	if (ringbuffer_pop(ring, &value)) {
		printf("ringbuffer_pop returned unsuccessful\n");
		return 1;
	}

	if (value != 1) {
		printf("Expected value 1, but got %d\n", value);
		return 1;
	}

	return 0;
}

int main(int argc, char** argv) {

	//return smoketest();

	//Declare buffer and value
	ringbuffer_h ring; //initialize ringbuffer
	int32_t value; //initialize int32_t value
	//Testing
	ring = ringbuffer_init(10);
	getRingInfo(ring);
	getValues(ring);
	FillBuffer(ring); //Adds 9 values into the buffer
	getValues(ring);
	getRingInfo(ring);
	ringbuffer_pop(ring,&value);
	ringbuffer_pop(ring,&value);
	ringbuffer_pop(ring,&value);
	ringbuffer_pop(ring,&value);
	ringbuffer_pop(ring,&value);
	ringbuffer_pop(ring,&value);
	ringbuffer_pop(ring,&value);
	ringbuffer_pop(ring,&value);
	ringbuffer_pop(ring,&value);
	getValues(ring);
	getRingInfo(ring);
	printf("Remaining Slots: %d\n",ringbuffer_remaining(ring));
	printf("Ringbuffer Empty? (0 empty, 1 not empty) :%d\n",ringbuffer_empty(ring));
	printf("Ringbuffer Full? (0 full, 1 not full) :%d\n",ringbuffer_full(ring));
	printf("Ringbuffer Destroyed? (0 success) :%d\n",ringbuffer_destroy(ring));

}
