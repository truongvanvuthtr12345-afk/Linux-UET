#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

int main(void)
{
    pid_t pid1, pid2, pid3;
    int status;

    pid1 = fork();

    if (pid1 < 0)
    {
        perror("fork");
        return 1;
    }

    if (pid1 == 0)
    {
        printf("Child 1 PID: %d\n", getpid());
        execlp("ls", "ls", "-l", (char *)NULL);
        perror("execlp ls");
        exit(1);
    }

    pid2 = fork();

    if (pid2 < 0)
    {
        perror("fork");
        return 1;
    }

    if (pid2 == 0)
    {
        printf("Child 2 PID: %d\n", getpid());
        execlp("pwd", "pwd", (char *)NULL);
        perror("execlp pwd");
        exit(1);
    }

    pid3 = fork();

    if (pid3 < 0)
    {
        perror("fork");
        return 1;
    }

    if (pid3 == 0)
    {
        printf("Child 3 PID: %d\n", getpid());
        sleep(10);
        printf("Child 3 finished.\n");
        exit(0);
    }

    printf("Parent PID: %d\n", getpid());
    printf("Child 1 PID: %d\n", pid1);
    printf("Child 2 PID: %d\n", pid2);
    printf("Child 3 PID: %d\n", pid3);

    waitpid(pid1, &status, 0);
    printf("Child 1 exit code: %d\n", WIFEXITED(status) ? WEXITSTATUS(status) : -1);

    waitpid(pid2, &status, 0);
    printf("Child 2 exit code: %d\n", WIFEXITED(status) ? WEXITSTATUS(status) : -1);

    sleep(3);

    if (kill(pid3, 0) == 0)
    {
        printf("Parent: sending SIGTERM to Child 3.\n");
        kill(pid3, SIGTERM);
    }

    waitpid(pid3, &status, 0);

    printf("All child processes finished.\n");
    printf("Parent exits.\n");

    return 0;
}
