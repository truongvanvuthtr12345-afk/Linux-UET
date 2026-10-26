#include <stdio.h>
#include <pthread.h>

int a[100], n;
int result[2] = {0, 0};

typedef struct {
    int start, end, id;
} Data;

void *countPositive(void *arg) {
    Data *d = (Data *)arg;

    for (int i = d->start; i < d->end; i++)
        if (a[i] > 0)
            result[d->id]++;

    return NULL;
}

int main() {
    pthread_t t[2];
    Data d[2];
    int parallel, sequential = 0;

    printf("Nhap N: ");
    scanf("%d", &n);

    if (n < 1 || n > 100) return 1;

    printf("Nhap %d so nguyen: ", n);
    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);

    d[0] = (Data){0, n / 2, 0};
    d[1] = (Data){n / 2, n, 1};

    for (int i = 0; i < 2; i++)
        pthread_create(&t[i], NULL, countPositive, &d[i]);

    for (int i = 0; i < 2; i++)
        pthread_join(t[i], NULL);

    parallel = result[0] + result[1];

    for (int i = 0; i < n; i++)
        if (a[i] > 0) sequential++;

    printf("Positive: %d\n", parallel);
    printf("Sequential: %d\n", sequential);

    return 0;
}
