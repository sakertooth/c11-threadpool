#pragma once
#include <threads.h>
#include <stdbool.h>
#include "queue.h"

typedef struct
{
    queue_t* workqueue;
    thrd_t* workers;
    size_t worker_count;
    cnd_t cnd;
    mtx_t mtx;
    bool complete;
}threadpool_t;

typedef struct 
{
    void (*fn)(void*);
    void *arg;
}work_t;

static int threadpool_thread(void *arg)
{
    threadpool_t *threadpool = arg;
    while (true)
    {
        mtx_lock(&threadpool->mtx);
        if (!threadpool->complete && threadpool->workqueue->size == 0) 
        {
            cnd_wait(&threadpool->cnd, &threadpool->mtx);
        }
        
        if (threadpool->complete && threadpool->workqueue->size == 0) 
        {
            mtx_unlock(&threadpool->mtx);
            break;
        }

        work_t work;
        if (queue_dequeue(threadpool->workqueue, &work) == -1) 
        {
            mtx_unlock(&threadpool->mtx);
            continue;
        }
        mtx_unlock(&threadpool->mtx);
        work.fn(work.arg);
    }
    return 0;
}

threadpool_t* threadpool_create(size_t worker_count, size_t queuesize) 
{
    threadpool_t *threadpool = malloc(sizeof(*threadpool));
    threadpool->workqueue = queue_create(queuesize, sizeof(work_t));
    threadpool->workers = malloc(worker_count * sizeof(thrd_t));
    threadpool->worker_count = worker_count;
    threadpool->complete = false;

    cnd_init(&threadpool->cnd);
    mtx_init(&threadpool->mtx, mtx_plain);

    for (int i = 0; i < worker_count; i++) 
    {
        thrd_create(&threadpool->workers[i], threadpool_thread, threadpool);
    }
    return threadpool;
}

void threadpool_enqueue(threadpool_t *threadpool, void (*fn)(void*), void *arg)
{
    work_t work = {fn, arg};
    mtx_lock(&threadpool->mtx);
    queue_enqueue(threadpool->workqueue, &work);
    mtx_unlock(&threadpool->mtx);
    cnd_signal(&threadpool->cnd);
}

void threadpool_join(threadpool_t *threadpool)
{   
    mtx_lock(&threadpool->mtx);
    threadpool->complete = true;
    mtx_unlock(&threadpool->mtx);
    cnd_broadcast(&threadpool->cnd);

    for (int i = 0; i < threadpool->worker_count; i++) 
    {
        thrd_join(threadpool->workers[i], NULL);
    }
}

void threadpool_free(threadpool_t *threadpool)
{
    queue_free(threadpool->workqueue);
    cnd_destroy(&threadpool->cnd);
    mtx_destroy(&threadpool->mtx);
    free(threadpool->workers);
    free(threadpool);
}