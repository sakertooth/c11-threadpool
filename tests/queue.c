#include <queue.h>
#include <stdio.h>

int main() 
{
    queue_t *queue = queue_create(256, sizeof(int));

    int a = 1, b = 2, c = 3;
    queue_enqueue(queue, &a);
    queue_enqueue(queue, &b);
    queue_enqueue(queue, &c);

    for (int i = 0; i < queue->size; i++) 
    {
        printf("%d\n", ((int*)queue->data)[i]);
    }
    printf("Enqueued 3 items\n\n");

    int ap;
    queue_dequeue(queue, &ap);

    for (int i = 0; i < queue->size; i++) 
    {
        printf("%d\n", ((int*)queue->data)[i]);
    }
    printf("Dequeued 1 item\n\n");

    queue_enqueue(queue, &a);
 
    for (int i = 0; i < queue->size; i++) 
    {
        printf("%d\n", ((int*)queue->data)[i]);
    }
    printf("Enqueued 1 item\n");

    return 0;
}