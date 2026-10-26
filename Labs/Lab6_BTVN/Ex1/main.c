#include <stdio.h>
#include <pthread.h>

int a[100], n;
int result[3][3] = {0};

typedef struct {
    int start, end, id;
} Data;

void *count(void *arg) {
    Data *d = (Data *)arg;

    for (int i = d->start; i < d->end; i++) {
        if (a[i] < 0)
            result[d->id][0]++;
        else if (a[i] > 0)
            result[d->id][1]++;
        else
            result[d->id][2]++;
    }

    return NULL;
}

int main() {
    pthread_t t[3];
    Data d[3];
    int negative = 0, positive = 0, zero = 0;

    printf("Nhap N: ");
    scanf("%d", &n);

    if (n < 1 || n > 100)
        return 1;

    printf("Nhap %d so nguyen: ", n);
    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);

    for (int i = 0; i < 3; i++) {
        d[i].start = i * n / 3;
        d[i].end = (i + 1) * n / 3;
        d[i].id = i;

        pthread_create(&t[i], NULL, count, &d[i]);
    }

    for (int i = 0; i < 3; i++)
        pthread_join(t[i], NULL);

    for (int i = 0; i < 3; i++) {
        negative += result[i][0];
        positive += result[i][1];
        zero += result[i][2];
    }

    printf("Negative: %d; Positive: %d; Zero: %d\n",
           negative, positive, zero);

    if (negative + positive + zero == n)
        printf("Check: OK (%d = %d)\n", n, negative + positive + zero);

    return 0;
}
