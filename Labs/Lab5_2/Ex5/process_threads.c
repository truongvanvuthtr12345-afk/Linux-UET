#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/wait.h>

#define N 10

int a[N] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

typedef struct {
    int start;
    int end;
    long long result;
} Data;

void *sum_array(void *arg)
{
    Data *d = (Data *)arg;
    d->result = 0;

    for (int i = d->start; i < d->end; i++)
        d->result += a[i];

    return NULL;
}

void *count_even(void *arg)
{
    Data *d = (Data *)arg;
    d->result = 0;

    for (int i = d->start; i < d->end; i++)
        if (a[i] % 2 == 0)
            d->result++;

    return NULL;
}

int main(void)
{
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");
        return 1;
    }

    if (pid == 0) {
        pthread_t t1, t2;
        Data d1 = {0, N / 2, 0};
        Data d2 = {N / 2, N, 0};

        pthread_create(&t1, NULL, count_even, &d1);
        pthread_create(&t2, NULL, count_even, &d2);
        pthread_join(t1, NULL);
        pthread_join(t2, NULL);

        long long total = d1.result + d2.result;

        FILE *f = fopen("child.txt", "w");
        if (f == NULL) {
            perror("child.txt");
            exit(1);
        }

        fprintf(f, "Child process: even count = %lld\n", total);
        fclose(f);

        printf("Child: even count = %lld\n", total);
        exit(0);
    } else {
        pthread_t t1, t2;
        Data d1 = {0, N / 2, 0};
        Data d2 = {N / 2, N, 0};

        pthread_create(&t1, NULL, sum_array, &d1);
        pthread_create(&t2, NULL, sum_array, &d2);
        pthread_join(t1, NULL);
        pthread_join(t2, NULL);

        long long total = d1.result + d2.result;

        FILE *f = fopen("parent.txt", "w");
        if (f == NULL) {
            perror("parent.txt");
            return 1;
        }

        fprintf(f, "Parent process: sum = %lld\n", total);
        fclose(f);

        printf("Parent: sum = %lld\n", total);

        int status;
        waitpid(pid, &status, 0);

        printf("\n--- parent.txt ---\n");
        system("cat parent.txt");
        printf("--- child.txt ---\n");
        system("cat child.txt");
    }

    return 0;
}
