#include <stdio.h>
#include <unistd.h>

int main(void)
{
    int x = 10;

    pid_t pid = fork();

    if (pid < 0)
    {
        perror("fork");
        return 1;
    }

    if (pid > 0)
    {
        x = 20;
        printf("Parent: PID=%d, x=%d, address=%p\n", getpid(), x, (void *)&x);
    }
    else
    {
        x = 30;
        printf("Child: PID=%d, x=%d, address=%p\n", getpid(), x, (void *)&x);
    }

    return 0;
}
