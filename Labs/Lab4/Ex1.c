#include <stdio.h>
#include <unistd.h>

int main()
{
    int number = 10;

    pid_t pid = fork();

    if (pid < 0)
    {
        printf("Fork failed\n");
        return 1;
    }

    if (pid == 0)
    {
        number += 5;
        printf("Child: PID = %d, number = %d\n", getpid(), number);
    }
    else
    {
        number -= 5;
        printf("Parent: PID = %d, number = %d\n", getpid(), number);
    }

    return 0;
}
