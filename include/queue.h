#pragma once
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

typedef struct 
{
    void *data;
    int write_index;
    size_t size;
    size_t element_size;
    size_t capacity;
}queue_t;

/* Creates a queue with the specified capacity and a size for each element. Returns the queue created. */
queue_t* queue_create(size_t capacity, size_t element_size) 
{
    queue_t *queue = malloc(sizeof(*queue));
    queue->data = malloc(capacity * element_size);
    queue->write_index = 0;
    queue->size = 0;
    queue->element_size = element_size;
    queue->capacity = capacity;
    return queue;
}

/* Enqueue an item with a specified size and block if the queue is full. Returns -1 on error, 0 on success. */
int queue_enqueue(queue_t *queue, void *item) 
{
    if (queue->capacity == 0) return -1;

    /*
        1. Block until the queue is no longer full.
        2. Enqueue the item by appending it, which increments the write_index.
        3. Increase the queue's size.
    */

    while (queue->size == queue->capacity) {}
    memcpy(&((char*)queue->data)[queue->write_index++ * queue->element_size], item, queue->element_size);
    ++queue->size;
    return 0;
}

/* Dequeue an item. Returns -1 on error, 0 on success. */
int queue_dequeue(queue_t *queue, void *dest) 
{
    if (queue->capacity == 0 || queue->size == 0) return -1;

    /*
        1. Copy the first element in the queue to dest, 
        2. Shift the whole array after the first element to the left.
        3. Move the write index to the end of the queue.
    */

    memcpy(dest, queue->data, queue->element_size);
    memmove(queue->data, &((char*)queue->data)[queue->element_size], --queue->size * queue->element_size);
    queue->write_index = queue->size;
    return 0;
}

/* Free the queue back to the heap. */
void queue_free(queue_t *queue)
{
    free(queue->data);
    free(queue);
}
