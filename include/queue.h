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

int queue_enqueue(queue_t *queue, void *item) 
{
    if (queue->capacity == 0) return -1;

    while (queue->size == queue->capacity) {}
    memcpy(&((char*)queue->data)[queue->write_index++ * queue->element_size], item, queue->element_size);
    ++queue->size;

    if (queue->write_index == queue->capacity - 1) queue->write_index = 0;
    return 0;
}

int queue_dequeue(queue_t *queue, void *dest) 
{
    if (queue->capacity == 0 || queue->size == 0) return -1;

    memcpy(dest, queue->data, queue->element_size);
    memmove(queue->data, &((char*)queue->data)[queue->element_size], --queue->size * queue->element_size);
    return 0;
}

void queue_free(queue_t *queue) 
{
    free(queue->data);
}