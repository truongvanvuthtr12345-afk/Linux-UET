#include <stdio.h>
#include <pthread.h>

int a[4][4];
int sum[4] = {0, 0, 0, 0};

void *rowSum(void *arg) {
    int row = *(int *)arg;

    for (int j = 0; j < 4; j++)
        sum[row] += a[row][j];

    return NULL;
}

int main() {
    pthread_t t[4];
    int row[4];

    printf("Nhap ma tran 4x4:\n");
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            scanf("%d", &a[i][j]);

    for (int i = 0; i < 4; i++) {
        row[i] = i;
        pthread_create(&t[i], NULL, rowSum, &row[i]);
    }

    for (int i = 0; i < 4; i++)
        pthread_join(t[i], NULL);

    printf("Row sums:");
    for (int i = 0; i < 4; i++)
        printf(" %d", sum[i]);

    printf("\n");
    return 0;
}
