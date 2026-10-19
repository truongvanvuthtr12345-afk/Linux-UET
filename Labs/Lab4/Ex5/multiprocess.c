p`#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: %s N\n", argv[0]);
        return 1;
    }

    int N = atoi(argv[1]);

    if (N < 1)
    {
        printf("N must be positive.\n");
        return 1;
    }

    pid_t pid1 = fork();

    if (pid1 < 0)
    {
        perror("fork");
        return 1;
    }

    if (pid1 == 0)
    {
        long sum = 0;

        for (int i = 1; i <= N; i++)
            sum += i;

        printf("Child 1: PID=%d, Sum=%ld\n", getpid(), sum);
        return 0;
    }

    pid_t pid2 = fork();

    if (pid2 < 0)
    {
        perror("fork");
        return 1;
    }

    if (pid2 == 0)
    {
        long sum = 0;

        for (int i = 2; i <= N; i += 2)
            sum += i;

        printf("Child 2: PID=%d, Even sum=%ld\n", getpid(), sum);
        return 0;
    }

    pid_t pid3 = fork();

    if (pid3 < 0)
    {
        perror("fork");
        return 1;
    }

    if (pid3 == 0)
    {
        long sum = 0;

        for (int i = 1; i <= N; i += 2)
            sum += i;

        printf("Child 3: PID=%d, Odd sum=%ld\n", getpid(), sum);
        return 0;
    }

    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);
    waitpid(pid3, NULL, 0);

    printf("Parent: All children finished.\n");

    return 0;
}
