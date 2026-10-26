#include <stdio.h>
#include <pthread.h>

int A[2][2] = {{1, 2}, {3, 4}};
int B[2][2] = {{5, 6}, {7, 8}};
int C[2][2];

typedef struct {
    int i, j;
} Data;

void *multiply(void *arg) {
    Data *d = (Data *)arg;

    C[d->i][d->j] =
        A[d->i][0] * B[0][d->j] +
        A[d->i][1] * B[1][d->j];

    return NULL;
}

int main() {
    pthread_t t[4];
    Data d[4];
    int k = 0;

    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++) {
            d[k] = (Data){i, j};
            pthread_create(&t[k], NULL, multiply, &d[k]);
            k++;
        }

    for (int i = 0; i < 4; i++)
        pthread_join(t[i], NULL);

    printf("C = [%d %d; %d %d]\n",
           C[0][0], C[0][1], C[1][0], C[1][1]);

    int S[2][2] = {{0, 0}, {0, 0}};

    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++)
            for (int x = 0; x < 2; x++)
                S[i][j] += A[i][x] * B[x][j];

    printf("Sequential = [%d %d; %d %d]\n",
           S[0][0], S[0][1], S[1][0], S[1][1]);

    return 0;
}
