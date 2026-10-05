#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(void)
{
    int pipefd[2];
    pid_t pid;

    if (pipe(pipefd) == -1)
    {
        perror("pipe");
        return 1;
    }

    pid = fork();

    if (pid < 0)
    {
        perror("fork");
        return 1;
    }

    if (pid == 0)
    {
        // Child: ls -> pipe
        close(pipefd[0]);

        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[1]);

        execlp("ls", "ls", NULL);

        perror("execlp ls");
        exit(1);
    }
    else
    {
        // Parent: pipe -> sort -r
        close(pipefd[1]);

        dup2(pipefd[0], STDIN_FILENO);
        close(pipefd[0]);

        waitpid(pid, NULL, 0);

        execlp("sort", "sort", "-r", NULL);

        perror("execlp sort");
        exit(1);
    }

    return 0;
}
