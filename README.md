# c11-threadpool
Just a simple threadpool, based on C11 which uses the new threads.h library.

## queue
Basic queue with enqueue and dequeue functions.  
Similar to a vector, the queue's capacity will double everytime its capacity is met by its size.

| Function  | Description |
| ------------- | ------------- |
| _queue_t *queue_create(size_t capacity, size_t element_size)_  | Creates a queue with the specified capacity and a size for each element. Returns the queue created.  |
| _int queue_enqueue(queue_t *queue, void *item, size_t item_size)_ | Enqueue an item with a specified size. Returns -1 on error, 0 on success. |
| _int queue_dequeue(queue_t *queue, void *dest)_ | Dequeue an item. Returns -1 on error, 0 on success. |
| _void queue_free(queue_t *queue)_ | Free the queue back to the heap. |

## threadpool
A very simple threadpool which uses basic enqueue and join functions.

| Function  | Description |
| ------------- | ------------- |
| _threadpool_t* threadpool_create(size_t worker_count, size_t queuesize)_ | Creates a threadpool with the specified number of workers and queuesize. Returns the threadpool created. |
| _void threadpool_enqueue(threadpool_t *threadpool, void (*fn)(void*), void *arg)_  | Enqueue an action to the threadpool. |
| _void threadpool_join(threadpool_t *threadpool)_ | Wait for all threads in the thread pool to finish. This will also wait for all tasks in the queue to be handled. |
| _void threadpool_free(threadpool_t *threadpool)_ | Free the threadpool back to the heap. |


## License
This C11 threadpool implementation is licensed under the [MIT](LICENSE) license.
