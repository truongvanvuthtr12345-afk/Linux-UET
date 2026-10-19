#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
int detached_done = 0;

void *worker_A(void *arg)
{
    printf("Thread A: Working...\n");
    sleep(1);
    printf("Thread A: Finished.\n");
    return NULL;
}

void *worker_B(void *arg)
{
    printf("Thread B: Working...\n");
    sleep(2);
    printf("Thread B: Finished.\n");

    pthread_mutex_lock(&mutex);
    detached_done = 1;
    pthread_cond_signal(&cond);
    pthread_mutex_unlock(&mutex);

    return NULL;
}

int main(void)
{
    pthread_t A, B;

    pthread_create(&A, NULL, worker_A, NULL);
    pthread_create(&B, NULL, worker_B, NULL);

    pthread_detach(B);

    pthread_join(A, NULL);
    printf("Main: Thread A joined.\n");

    pthread_mutex_lock(&mutex);
    while (!detached_done)
        pthread_cond_wait(&cond, &mutex);
    pthread_mutex_unlock(&mutex);

    printf("Main: Thread B completed (detached).\n");

    pthread_cond_destroy(&cond);
    pthread_mutex_destroy(&mutex);

    return 0;
}
