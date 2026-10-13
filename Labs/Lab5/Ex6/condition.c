#include <stdio.h>
#include <pthread.h>

int data = 0;
int ready = 0;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

void *thread_A(void *arg)
{
    pthread_mutex_lock(&mutex);

    printf("Thread A: Waiting for data...\n");

    while (!ready)
    {
        pthread_cond_wait(&cond, &mutex);
    }

    printf("Thread A: Received data = %d\n", data);

    pthread_mutex_unlock(&mutex);
    return NULL;
}

void *thread_B(void *arg)
{
    printf("Thread B: Preparing data...\n");

    pthread_mutex_lock(&mutex);

    data = 100;
    ready = 1;

    pthread_cond_signal(&cond);
    pthread_mutex_unlock(&mutex);

    return NULL;
}

int main(void)
{
    pthread_t A, B;

    pthread_create(&A, NULL, thread_A, NULL);
    pthread_create(&B, NULL, thread_B, NULL);

    pthread_join(A, NULL);
    pthread_join(B, NULL);

    pthread_cond_destroy(&cond);
    pthread_mutex_destroy(&mutex);

    return 0;
}
