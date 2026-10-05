#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

int main(void)
{
    int pipefd[2];
    pid_t pid;
    char buffer[100];

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

    if (pid > 0)
    {
        close(pipefd[0]);

        char message[] = "Hello from parent";
        write(pipefd[1], message, strlen(message) + 1);

        close(pipefd[1]);
        wait(NULL);
    }
    else
    {
        close(pipefd[1]);

        read(pipefd[0], buffer, sizeof(buffer));
        printf("Child received: %s\n", buffer);

        close(pipefd[0]);
    }

    return 0;
}
