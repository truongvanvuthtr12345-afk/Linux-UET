#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: %s seconds\n", argv[0]);
        return 1;
    }

    int seconds = atoi(argv[1]);

    pid_t pid = fork();

    if (pid < 0)
    {
        perror("fork");
        return 1;
    }

    if (pid == 0)
    {
        printf("Child: Working for %d seconds...\n", seconds);
        sleep(seconds);
        printf("Child: Work completed!\n");
    }
    else
    {
       
        printf("Parent: Child has finished. Continuing...\n");
    }

    return 0;
}
