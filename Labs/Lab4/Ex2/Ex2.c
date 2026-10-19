l7778888888888888888888888888#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main()
{
    pid_t pid = fork();
    if (pid < 0)
    {
        perror("fork");
        return 1;
    }
    if (pid == 0)
    {
        execlp("ls", "ls", "-l", NULL);
        perror("execlp");
        exit(1);
    }
    else
    {
        wait(NULL);
        printf("Command finished.\n");
    }
    return 0;
}
