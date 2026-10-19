#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

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
        printf("Child: Dang lam viec...\n");
        sleep(3);
        printf("Child: Hoan thanh!\n");
    }
    else
    {
        wait(NULL);
        printf("Parent: Tiep tuc cong viec sau khi child ket thuc.\n");
    }

    return 0;
}

