#pragma once
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <stdio.h>

typedef struct 
{
    void *data;
    size_t size;
    size_t element_size;
    size_t capacity;
}queue_t;

queue_t* queue_create(size_t capacity, size_t element_size) 
{
    queue_t *queue = malloc(sizeof(*queue));
    queue->capacity = capacity > 0 ? capacity : 2;
    queue->element_size = element_size;
    queue->size = 0;
    queue->data = malloc(queue->capacity * queue->element_size);
    return queue;
}

int queue_enqueue(queue_t *queue, void *item, size_t item_size) 
{
    if (queue->element_size != item_size) return -1;
    memcpy(&((char*)queue->data)[queue->size++ * queue->element_size], item, item_size);

    if (queue->size == queue->capacity)
    {
        queue->capacity *= 2;
        queue->data = realloc(queue->data, queue->capacity * queue->element_size);

        if (queue->data == NULL)
        {
            fprintf(stderr, "Failure to reallocate (queue)");
            abort();
            return -1;
        }
    }
    return 0;
}

int queue_dequeue(queue_t *queue, void *dest)
{
    if (queue->size == 0) return -1;
    
    memcpy(dest, queue->data, queue->element_size);
    memmove(queue->data, &((char*)queue->data)[queue->element_size], --queue->size);
    memmove(&((char*)queue->data)[queue->element_size], &((char*)queue->data)[queue->element_size * 2], queue->element_size);
    return 0;
}

void queue_free(queue_t *queue)
{
    free(queue->data);
    free(queue);
}