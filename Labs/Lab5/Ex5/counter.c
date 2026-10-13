#include <stdio.h>
#include <pthread.h>

#define ITERATIONS 100000

long long counter = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *count_without_mutex(void *arg)
{
    for (int i = 0; i < ITERATIONS; i++)
        counter++;

    return NULL;
}

void *count_with_mutex(void *arg)
{
    for (int i = 0; i < ITERATIONS; i++)
    {
        pthread_mutex_lock(&mutex);
        counter++;
        pthread_mutex_unlock(&mutex);
    }

    return NULL;
}

void run_test(void *(*function)(void *), const char *name)
{
    pthread_t t1, t2;
    counter = 0;

    pthread_create(&t1, NULL, function, NULL);
    pthread_create(&t2, NULL, function, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("%s: counter = %lld\n", name, counter);
}

int main(void)
{
    run_test(count_without_mutex, "Ban A (khong mutex)");
    run_test(count_with_mutex, "Ban B (co mutex)");

    pthread_mutex_destroy(&mutex);
    return 0;
}
