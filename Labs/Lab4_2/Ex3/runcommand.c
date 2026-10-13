#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Usage: %s command [arguments...]\n", argv[0]);
        return 1;
    }

    pid_t pid = fork();

    if (pid < 0)
    {
        perror("fork");
        return 1;
    }

    if (pid == 0)
    {
        execvp(argv[1], &argv[1]);

        perror("execvp");
        exit(1);
    }
    else
    {
        wait(NULL);
        printf("Command finished.\n");
    }

    return 0;
}
