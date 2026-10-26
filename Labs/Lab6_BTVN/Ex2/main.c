#include <stdio.h>
#include <pthread.h>

int a[100], n;
long long result[4] = {0};

typedef struct {
    int start, end, id;
} Data;

void *sumPart(void *arg) {
    Data *d = (Data *)arg;

    for (int i = d->start; i < d->end; i++)
        result[d->id] += a[i];

    return NULL;
}

int main() {
    FILE *f = fopen("numbers.txt", "r");
    if (f == NULL) {
        printf("Khong mo duoc numbers.txt\n");
        return 1;
    }

    fscanf(f, "%d", &n);
    if (n < 1 || n > 100) {
        fclose(f);
        return 1;
    }

    for (int i = 0; i < n; i++)
        fscanf(f, "%d", &a[i]);
    fclose(f);

    pthread_t t[4];
    Data d[4];

    for (int i = 0; i < 4; i++) {
        d[i].start = i * n / 4;
        d[i].end = (i + 1) * n / 4;
        d[i].id = i;
        pthread_create(&t[i], NULL, sumPart, &d[i]);
    }

    long long total = 0;

    for (int i = 0; i < 4; i++) {
        pthread_join(t[i], NULL);
        total += result[i];
    }

    FILE *out = fopen("result.txt", "w");
    if (out == NULL) return 1;

    fprintf(out, "Total = %lld\n", total);
    fclose(out);

    printf("Total = %lld\n", total);
    return 0;
}
