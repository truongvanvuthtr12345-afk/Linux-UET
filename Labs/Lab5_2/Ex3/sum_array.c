#include <stdio.h>
#include <pthread.h>

#define MAX 1000

int a[MAX];
int n;

typedef struct
{
    int start;
    int end;
    long long sum;
} ThreadData;

void *calculate_sum(void *arg)
{
    ThreadData *data = (ThreadData *)arg;
    data->sum = 0;

    for (int i = data->start; i < data->end; i++)
    {
        data->sum += a[i];
    }

    return NULL;
}

int main(void)
{
    pthread_t t1, t2;
    ThreadData d1, d2;
    long long parallel_sum, sequential_sum = 0;

    printf("Nhap N (N <= 1000): ");
    if (scanf("%d", &n) != 1 || n < 1 || n > MAX)
    {
        printf("N khong hop le!\n");
        return 1;
    }

    for (int i = 0; i < n; i++)
    {
        printf("a[%d] = ", i);
        if (scanf("%d", &a[i]) != 1)
        {
            printf("Du lieu khong hop le!\n");
            return 1;
        }
        sequential_sum += a[i];
    }

    d1.start = 0;
    d1.end = n / 2;
    d2.start = n / 2;
    d2.end = n;

    pthread_create(&t1, NULL, calculate_sum, &d1);
    pthread_create(&t2, NULL, calculate_sum, &d2);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    parallel_sum = d1.sum + d2.sum;

    printf("Tong bang 2 threads = %lld\n", parallel_sum);
    printf("Tong tinh tuan tu = %lld\n", sequential_sum);

    return 0;
}
