#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

void *worker(void *arg)
{
    printf("PID: %d, Thread ID: %lu\n",
           (int)getpid(), (unsigned long)pthread_self());
    return NULL;
}

int main(void)
{
    pthread_t t1, t2;

    pthread_create(&t1, NULL, worker, NULL);
    pthread_create(&t2, NULL, worker, NULL);

    printf("Main PID: %d\n", (int)getpid());
    printf("Hai worker co cung Thread ID khong? %s\n",
           pthread_equal(t1, t2) ? "Co" : "Khong");

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    return 0;
}
