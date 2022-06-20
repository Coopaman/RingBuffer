#include "ringbuffer.h"
/*
 * ringbuffer_init
 *
 * Initialize a new int32_t ringbuffer with given size in elements
 *
 * @param size Size in elements
 *
 * @return ringbuffer handle or NULL on error
 */
ringbuffer_h ringbuffer_init(int size) {
	// Implement init here
	ringbuffer_h ringbuffer = malloc(size*sizeof(int)); //Initialize ringbuffer, allocating memory
	ringbuffer->buffer = malloc(size*sizeof(int)); //allocating memory for buffer data
	ringbuffer->bufferMax = size; //set size of buffer
	ringbuffer->head = 0; //set head pointer position to 0
	ringbuffer->tail = 0; //set tail pointer position to 0

	//return an error if unable to return ringbuffer handle
	if(ringbuffer->buffer == NULL)
	{
		errno = ENOSYS;
		return NULL;
	}

	else
	{
		return ringbuffer; 	//return the ringbuffer handle
	}

}

/*
 * ringbuffer_push
 *
 * Push a new int32 element onto the given ringbuffer
 *
 * @param ring  ringbuffer handle to add an element to
 * @param value int32 value to push
 *
 * @return 0 on success, other on failure
 */
int ringbuffer_push(ringbuffer_h ring, int32_t value) {
	// Implement push here
	if(ringbuffer_full(ring) == 1) //Check to make sure buffer is not full
	{
		ring->buffer[ring->head] = value; //Loads the value on buffer
		ring->head = (ring->head + 1) % (ring->bufferMax); //increments the position of the head pointer
		return 0; //successful push
	}
//return an error if unable to push a value onto buffer
else
{
	errno = ENOSYS;
	return -1; //error
}

}

/*
 * ringbuffer_pop
 *
 * Pop a int32 element from the given ringbuffer
 *
 * @param ring  ringbuffer handle to add an element to
 * @param value pointer to int32 value populate with popped value
 *
 * @return 0 on success, other on failure
 */
int ringbuffer_pop(ringbuffer_h ring, int32_t *value) {
	// Implement pop here
	if(ringbuffer_empty(ring) == 1) //check to make sure buffer is not empty
	{
		//First pop the data and then move the tail pointer
		*value = ring->buffer[ring->tail]; //Reads the value on buffer
		ring->tail = (ring->tail + 1) % ring->bufferMax; //increments the position of the tail pointer
		return 0; //successful pop
	}
	//return an error if unable to pop a value from buffer
	else
	{
		errno = ENOSYS;
		return -1; //error
	}

}
/*
 * ringbuffer empty
 *
 * Check if a ringbuffer is empty
 *
 * @param ring ringbuffer to check
 *
 * @return 0 if empty, 1 if non-empty, negative on failure
 */
int ringbuffer_empty(ringbuffer_h ring) {
	// implement empty here
	if(ring->head == ring->tail) //buffer is empty if the head and tail pointer position are equal
	{
		return 0; //buffer is empty
	}

	else if(ring->head != ring->tail)
	{
		return 1; //buffer is not empty
	}

	else
	{
		errno = ENOSYS;
		return -1; //error
	}

}

/*
 * ringbuffer full
 *
 * Check if a ringbuffer is full
 *
 * @param ring ringbuffer to check
 *
 * @return 0 if full, 1 if non-full, negative on failure
 */
int ringbuffer_full(ringbuffer_h ring) {
	// implement full here
	//Assume buffer is full when there is one empty slot left
	if(ring->tail == (ring->head + 1) % ring->bufferMax) //buffer is full if tail pointer position equals head pointer position plus one empty space.
	{
		return 0; //buffer is full
	}

	else if(ring->tail != (ring->head + 1) % ring->bufferMax)
	{
		return 1; //buffer is not full
	}

	else
	{
		errno = ENOSYS;
		return -1; //error
	}

}

/*
 * ringbuffer remaining
 *
 * Get count of remaining slots in ringbuffer
 *
 * @param ring ringbuffer to check
 *
 * @return number of empty slots, negative on failure
 */
int ringbuffer_remaining(ringbuffer_h ring) {
	// implement remaining here
	//remaining slots equals the difference between the two pointers
	uint8_t spotsAvail;
	uint8_t pointerDifference;
	pointerDifference = abs(ring->head - ring->tail); //slot difference between the two pointers
	//if tail pointer < head pointer, slot difference is equal to number of slots taken
	if(ring->head > ring->tail) //if head pointer is ahead of tail pointer
	{
		spotsAvail = ring->bufferMax - pointerDifference; //empty slots equal to maximum buffer size minus the pointerDifference
		return spotsAvail; //return number of empty slots
	}

	else if(ring->head < ring->tail) //if tail pointer is ahead of head pointer
	{
		spotsAvail = pointerDifference; //empty slots equal to the difference between pointer position
		return spotsAvail; // return number of empty slots
	}

	else if(ringbuffer_empty(ring) == 0) //Check to see if ringbuffer is empty
	{
		return ring->bufferMax; //Remaining slots equal to buffer size(bufferMax)
	}

	else if (ringbuffer_full(ring) == 0) //Check to see if ringbuffer is full
	{
		return 0; //No slots available in buffer
	}

	else
	{
		errno = ENOSYS;
		return -1; //error
	}

}

/*
 * ringbuffer_destroy
 *
 * Destroy a given ringbuffer
 *
 * @param ring ringbuffer to destroy
 *
 * @return 0 on success, other on failure
 */
int ringbuffer_destroy(ringbuffer_h ring) {
	// implement destroy here

	//delete ring;
	free(ring->buffer); //deallocate memory from pointer
	free(ring); //deallocate memory from data buffer
	ring = NULL; //set struct pointer to NULL

	if(ring != NULL) //pointer memory not deallocated
	{
		errno = ENOSYS;
		return -1; //unsuccessful destroy, error
	}

	else
	{
		return 0; //successful destroy

	}

}
