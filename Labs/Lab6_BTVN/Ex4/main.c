#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MAX 200

int A[MAX][MAX], B[MAX][MAX];
long long C[MAX][MAX], S[MAX][MAX];
int n, threads;

typedef struct {
    int start, end;
} Data;

void *multiplyRows(void *arg) {
    Data *d = (Data *)arg;

    for (int i = d->start; i < d->end; i++)
        for (int j = 0; j < n; j++) {
            C[i][j] = 0;
            for (int k = 0; k < n; k++)
                C[i][j] += (long long)A[i][k] * B[k][j];
        }

    return NULL;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Dung: ./main N T\n");
        return 1;
    }

    n = atoi(argv[1]);
    threads = atoi(argv[2]);

    if (n < 1 || n > MAX || threads < 1 || threads > n)
        return 1;

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            A[i][j] = i + j;
            B[i][j] = i == j ? 1 : 0;
        }

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            S[i][j] = 0;
            for (int k = 0; k < n; k++)
                S[i][j] += (long long)A[i][k] * B[k][j];
        }

    pthread_t t[MAX];
    Data d[MAX];

    for (int i = 0; i < threads; i++) {
        d[i].start = i * n / threads;
        d[i].end = (i + 1) * n / threads;
        pthread_create(&t[i], NULL, multiplyRows, &d[i]);
    }

    for (int i = 0; i < threads; i++)
        pthread_join(t[i], NULL);

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (C[i][j] != S[i][j]) {
                printf("Ket qua sai!\n");
                return 1;
            }

    printf("Ket qua dung voi %d threads.\n", threads);
    return 0;
}
