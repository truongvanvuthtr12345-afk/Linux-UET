#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>

long count_bytes(const char *filename)
{
    int fd = open(filename, O_RDONLY);

    if (fd == -1)
    {
        perror(filename);
        return -1;
    }

    char buffer[1024];
    long total = 0;
    ssize_t n;

    while ((n = read(fd, buffer, sizeof(buffer))) > 0)
    {
        total += n;
    }

    close(fd);

    return total;
}

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("Usage: %s file1.txt file2.txt\n", argv[0]);
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
        long bytes = count_bytes(argv[2]);

        if (bytes >= 0)
            printf("Child: PID=%d, File=%s, Bytes=%ld\n",
                   getpid(), argv[2], bytes);
    }
    else
    {
        long bytes = count_bytes(argv[1]);

        if (bytes >= 0)
            printf("Parent: PID=%d, File=%s, Bytes=%ld\n",
                   getpid(), argv[1], bytes);

        wait(NULL);

        printf("Parent: Child finished.\n");
    }

    return 0;
}
