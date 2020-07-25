#include <queue.h>
#include <stdio.h>

int main() 
{
    queue_t *queue = queue_create(4, sizeof(int));
    int push[] = {1, 2, 3, 4};

    for (int i = 0; i < sizeof(push) / sizeof(int); i++) 
    {
        queue_push(queue, &push[i]);
    }
    printf("Queue: %d | %d | %d | %d\n", ((int*)queue->data)[0], ((int*)queue->data)[1], ((int*)queue->data)[2], ((int*)queue->data)[3]);

    int first_pop, second_pop;
    queue_pop(queue, &first_pop);
    queue_pop(queue, &second_pop);
    printf("Popped two values: %d and %d\n", first_pop, second_pop);

    queue_free(queue);
    return 0;
}