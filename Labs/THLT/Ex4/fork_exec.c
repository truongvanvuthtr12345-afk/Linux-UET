#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(void)
{
    pid_t child_pid = fork();

    if (child_pid < 0)
    {
        perror("fork");
        return 1;
    }

    if (child_pid == 0)
    {
        printf("Child: before execl\n");

        execlp("ls", "ls", "-l", NULL);

        perror("execlp");
        return 1;
    }
    else
    {
        waitpid(child_pid, NULL, 0);
        printf("Child finished\n");
    }

    return 0;
}

