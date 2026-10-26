#include <stdio.h>
#include <pthread.h>

#define N 10
#define N_thresh 5

int a[N] = {9, 4, 7, 1, 8, 2, 6, 3, 5, 10};

int partition(int l, int r) {
    int pivot = a[r], i = l - 1;

    for (int j = l; j < r; j++)
        if (a[j] < pivot) {
            i++;
            int temp = a[i];
            a[i] = a[j];
            a[j] = temp;
        }

    int temp = a[i + 1];
    a[i + 1] = a[r];
    a[r] = temp;

    return i + 1;
}

void quickSort(int l, int r) {
    if (l >= r) return;

    int p = partition(l, r);
    quickSort(l, p - 1);
    quickSort(p + 1, r);
}

typedef struct {
    int l, r;
} Data;

void *sortPart(void *arg) {
    Data *d = (Data *)arg;
    quickSort(d->l, d->r);
    return NULL;
}

int main() {
    pthread_t t1, t2;
    Data d1, d2;
    int p;

    printf("Input:");
    for (int i = 0; i < N; i++)
        printf(" %d", a[i]);

    p = partition(0, N - 1);

    d1 = (Data){0, p - 1};
    d2 = (Data){p + 1, N - 1};

    if (p > N_thresh && p < N - N_thresh) {
        pthread_create(&t1, NULL, sortPart, &d1);
        pthread_create(&t2, NULL, sortPart, &d2);

        pthread_join(t1, NULL);
        pthread_join(t2, NULL);
    } else {
        quickSort(d1.l, d1.r);
        quickSort(d2.l, d2.r);
    }

    printf("\nOutput:");
    for (int i = 0; i < N; i++)
        printf(" %d", a[i]);

    printf("\n");
    return 0;
}
