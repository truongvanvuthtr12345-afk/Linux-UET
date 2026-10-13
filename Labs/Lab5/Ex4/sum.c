#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *calculate_sum(void *arg)
{
    int n = *(int *)arg;
    long long *result = malloc(sizeof(long long));

    if (result == NULL)
        pthread_exit(NULL);

    *result = (long long)n * (n + 1) / 2;
    return result;
}

int main(void)
{
    int n;
    pthread_t thread;
    void *ret;

    printf("Nhap N (1 <= N <= 10000): ");
    if (scanf("%d", &n) != 1 || n < 1 || n > 10000)
    {
        printf("N khong hop le!\n");
        return 1;
    }

    if (pthread_create(&thread, NULL, calculate_sum, &n) != 0)
    {
        perror("pthread_create");
        return 1;
    }

    pthread_join(thread, &ret);

    if (ret == NULL)
    {
        printf("Khong cap phat duoc bo nho!\n");
        return 1;
    }

    printf("Tong tu 1 den %d = %lld\n", n, *(long long *)ret);
    free(ret);

    return 0;
}
