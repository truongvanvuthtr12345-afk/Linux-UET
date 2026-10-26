#include <stdio.h>
#include <pthread.h>

int a[12] = {1,2,3,4,5,6,7,8,9,10,11,12};
int sum = 0, even = 0;

void *tong(void *arg) {
    for (int i = 0; i < 12; i++)
        sum += a[i];
    return NULL;
}

void *dem(void *arg) {
    for (int i = 0; i < 12; i++)
        if (a[i] % 2 == 0) even++;
    return NULL;
}

int main() {
    pthread_t t1, t2;

    printf("Array:");
    for (int i = 0; i < 12; i++)
        printf(" %d", a[i]);
    printf("\n");

    pthread_create(&t1, NULL, tong, NULL);
    pthread_create(&t2, NULL, dem, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("Sum: %d; Even: %d\n", sum, even);
    return 0;
}
