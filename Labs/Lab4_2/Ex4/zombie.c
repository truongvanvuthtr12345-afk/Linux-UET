#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

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
        while (1)
        {
            printf("Child PID=%d: running...\n", getpid());
            fflush(stdout);
            sleep(1);
        }
    }
    else
    {
        sleep(5);

        printf("Parent: sending SIGTERM to child %d\n", pid);
        kill(pid, SIGTERM);

        wait(NULL);
        printf("Parent: child terminated and collected.\n");
    }

    return 0;
}
