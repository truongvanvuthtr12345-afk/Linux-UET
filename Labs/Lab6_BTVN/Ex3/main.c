#define _POSIX_C_SOURCE 199309L
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define N 1000000

int a[N];
long long part[4];

typedef struct {
    int start, end, id;
} Data;

void *sumPart(void *arg) {
    Data *d = (Data *)arg;
    long long s = 0;

    for (int i = d->start; i < d->end; i++)
        s += a[i];

    part[d->id] = s;
    return NULL;
}

double now() {
    struct timespec t;
    clock_gettime(CLOCK_MONOTONIC, &t);
    return t.tv_sec + t.tv_nsec / 1e9;
}

int main() {
    for (int i = 0; i < N; i++)
        a[i] = i % 100;

    for (int threads = 1; threads <= 4; threads *= 2) {
        double totalTime = 0;
        long long answer = 0;

        for (int run = 0; run < 5; run++) {
            pthread_t t[4];
            Data d[4];
            double start = now();

            if (threads == 1) {
                answer = 0;
                for (int i = 0; i < N; i++)
                    answer += a[i];
            } else {
                for (int i = 0; i < threads; i++) {
                    d[i].start = i * N / threads;
                    d[i].end = (i + 1) * N / threads;
                    d[i].id = i;
                    pthread_create(&t[i], NULL, sumPart, &d[i]);
                }

                answer = 0;
                for (int i = 0; i < threads; i++) {
                    pthread_join(t[i], NULL);
                    answer += part[i];
                }
            }

            totalTime += now() - start;
        }

        printf("%d thread(s): average %.6f seconds, sum = %lld\n",
               threads, totalTime / 5, answer);
    }

    return 0;
}
