#include <stdio.h>
#include <pthread.h>

int a[10] = {1,2,3,4,5,6,7,8,9,10};

typedef struct {
    int start;
    int end;
    int id;
} Data;

void *printArray(void *arg) {
    Data *d = (Data *)arg;

    printf("Thread %d:", d->id);
    for (int i = d->start; i < d->end; i++)
        printf(" %d", a[i]);
    printf("\n");

    return NULL;
}

int main() {
    pthread_t t[3];
    Data d[3] = {
        {0, 4, 1},
        {4, 7, 2},
        {7, 10, 3}
    };

    for (int i = 0; i < 3; i++)
        pthread_create(&t[i], NULL, printArray, &d[i]);

    for (int i = 0; i < 3; i++)
        pthread_join(t[i], NULL);

    return 0;
}
