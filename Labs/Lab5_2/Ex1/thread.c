#include <stdio.h>
#include <pthread.h>

void *worker(void *arg)
{
    pthread_t tid = pthread_self();
    printf("Hello from worker thread! ID = %lu\n", (unsigned long)tid);
    return NULL;
}

int main(void)
{
    pthread_t thread;

    if (pthread_create(&thread, NULL, worker, NULL) != 0)
    {
        perror("pthread_create");
        return 1;
    }

    pthread_join(thread, NULL);
    printf("Main: worker has finished.\n");

    return 0;
}
