#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: %s data.txt\n", argv[0]);
        return 1;
    }

    int fd = open(argv[1], O_RDONLY);

    if (fd == -1)
    {
        perror("open");
        return 1;
    }

    char buffer[11];

    int n = read(fd, buffer, 10);
    buffer[n] = '\0';
    printf("10 byte dau: %s\n", buffer);

    lseek(fd, 20, SEEK_SET);

    n = read(fd, buffer, 10);
    buffer[n] = '\0';
    printf("10 byte tu vi tri 20: %s\n", buffer);

    off_t size = lseek(fd, 0, SEEK_END);
    printf("File size: %ld bytes\n", size);

    close(fd);

    return 0;
}
