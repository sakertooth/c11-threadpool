#include <threadpool.h>
#include <stdio.h>

void fn(void *arg)
{
    printf("hello world\n");
    struct timespec s;
    s.tv_nsec = 0;
    s.tv_sec = 1;
    thrd_sleep(&s, NULL);
}

int main() 
{
    threadpool_t *tp = threadpool_create(4, 16);
    if (tp == NULL) return EXIT_FAILURE;

    for (int i = 0; i < 16; i++)
    {
        threadpool_enqueue(tp, fn, NULL);
    }

    threadpool_join(tp);
    threadpool_free(tp);
    return 0;
}
