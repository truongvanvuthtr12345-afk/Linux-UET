#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
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
        printf("Child: PID=%d, exiting.\n", getpid());
        fflush(stdout);
        exit(0);
    }
    else
    {
        printf("Parent: PID=%d, Child PID=%d\n", getpid(), pid);
        sleep(2);

        char path[64];
        snprintf(path, sizeof(path), "/proc/%d/stat", pid);

        FILE *f = fopen(path, "r");
        if (f != NULL)
        {
            int child_pid;
            char comm[256];
            char state;

            if (fscanf(f, "%d %255s %c", &child_pid, comm, &state) == 3)
                printf("Child state before wait: %c\n", state);

            fclose(f);
        }

        wait(NULL);
        printf("Parent: child collected.\n");
    }

    return 0;
}
