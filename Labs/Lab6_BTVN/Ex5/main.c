#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define N 10

int a[N], b[N];
int threshold, maxThreads;
int active = 1;

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

typedef struct {
    int left, right;
} Data;

void quickSort(int l, int r);

int partition(int l, int r) {
    int pivot = a[r], i = l - 1;

    for (int j = l; j < r; j++) {
        if (a[j] <= pivot) {
            i++;
            int temp = a[i];
            a[i] = a[j];
            a[j] = temp;
        }
    }

    int temp = a[i + 1];
    a[i + 1] = a[r];
    a[r] = temp;

    return i + 1;
}

void *sortThread(void *arg) {
    Data *d = (Data *)arg;

    quickSort(d->left, d->right);

    pthread_mutex_lock(&lock);
    active--;
    pthread_mutex_unlock(&lock);

    return NULL;
}

void quickSort(int l, int r) {
    if (l >= r) return;

    int p = partition(l, r);

    int leftSize = p - l;
    int rightSize = r - p;

    Data d;
    pthread_t t;
    int created = 0;

    if (leftSize > threshold) {
        pthread_mutex_lock(&lock);
        if (active < maxThreads) {
            active++;
            created = 1;
        }
        pthread_mutex_unlock(&lock);

        if (created) {
            d.left = l;
            d.right = p - 1;

            if (pthread_create(&t, NULL, sortThread, &d) == 0) {
                quickSort(p + 1, r);
                pthread_join(t, NULL);
            } else {
                pthread_mutex_lock(&lock);
                active--;
                pthread_mutex_unlock(&lock);
                quickSort(l, p - 1);
                quickSort(p + 1, r);
            }
            return;
        }
    }

    if (rightSize > threshold) {
        pthread_mutex_lock(&lock);
        if (active < maxThreads) {
            active++;
            created = 1;
        } else {
            created = 0;
        }
        pthread_mutex_unlock(&lock);

        if (created) {
            d.left = p + 1;
            d.right = r;

            if (pthread_create(&t, NULL, sortThread, &d) == 0) {
                quickSort(l, p - 1);
                pthread_join(t, NULL);
            } else {
                pthread_mutex_lock(&lock);
                active--;
                pthread_mutex_unlock(&lock);
                quickSort(l, p - 1);
                quickSort(p + 1, r);
            }
            return;
        }
    }

    quickSort(l, p - 1);
    quickSort(p + 1, r);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: ./main N_thresh MAX_THREADS\n");
        return 1;
    }

    threshold = atoi(argv[1]);
    maxThreads = atoi(argv[2]);

    if (threshold < 1 || maxThreads < 1) {
        printf("Invalid parameters\n");
        return 1;
    }

    int input[N] = {9, 4, 7, 1, 8, 2, 6, 3, 5, 10};

    for (int i = 0; i < N; i++) {
        a[i] = input[i];
        b[i] = input[i];
    }

    quickSort(0, N - 1);

    printf("Parallel result:");
    for (int i = 0; i < N; i++)
        printf(" %d", a[i]);

    for (int i = 0; i < N; i++)
        a[i] = b[i];

    quickSort(0, N - 1);

    printf("\nSequential result:");
    for (int i = 0; i < N; i++)
        printf(" %d", a[i]);

    printf("\n");
    pthread_mutex_destroy(&lock);
    return 0;
}
