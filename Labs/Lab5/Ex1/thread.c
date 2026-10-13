#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void *worker(void *arg)
{
    printf("Hello from worker thread\n");
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

    printf("Hello from main thread\n");

    pthread_join(thread, NULL);

    return 0;
}
