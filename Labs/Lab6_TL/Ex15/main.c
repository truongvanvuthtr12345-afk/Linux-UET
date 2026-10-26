#include <stdio.h>
#include <pthread.h>

int a[6] = {7, 2, 14, 5, 9, 3};
int even = 0, max = 0;

void *countEven(void *arg) {
    for (int i = 0; i < 6; i++)
        if (a[i] % 2 == 0)
            even++;

    return NULL;
}

void *findMax(void *arg) {
    max = a[0];

    for (int i = 1; i < 6; i++)
        if (a[i] > max)
            max = a[i];

    return NULL;
}

int main() {
    pthread_t t1, t2;

    pthread_create(&t1, NULL, countEven, NULL);
    pthread_create(&t2, NULL, findMax, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("Input:");
    for (int i = 0; i < 6; i++)
        printf(" %d", a[i]);

    printf("\nEven count: %d; Max: %d\n", even, max);
    return 0;
}
