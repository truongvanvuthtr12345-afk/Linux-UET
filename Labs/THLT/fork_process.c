#include <stdio.h>
#include <unistd.h>

int main(void)
{
    pid_t pid = fork();

    if (pid < 0)
    {
        perror("fork");
        return 1;
    }

    if (pid == 0)
    {
        printf("Child: PID=%d, PPID=%d\n", getpid(), getppid());
    }
    else
    {
        printf("Parent: PID=%d, Child PID=%d\n", getpid(), pid);
    }

    return 0;
}
