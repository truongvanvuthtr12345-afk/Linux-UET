#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("Usage: %s source.txt destination.txt\n", argv[0]);
        return 1;
    }

    int source = open(argv[1], O_RDONLY);
    if (source == -1)
    {
        perror("open source");
        return 1;
    }

    int destination = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (destination == -1)
    {
        perror("open destination");
        close(source);
        return 1;
    }

    char buffer[1024];
    ssize_t bytesRead;

    while ((bytesRead = read(source, buffer, sizeof(buffer))) > 0)
    {
        write(destination, buffer, bytesRead);
    }

    close(source);
    close(destination);

    return 0;
}
