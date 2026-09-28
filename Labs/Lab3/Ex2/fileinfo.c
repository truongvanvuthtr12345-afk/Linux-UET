#include <stdio.h>
#include <sys/stat.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    struct stat fileStat;

    if (stat(argv[1], &fileStat) == -1)
    {
        perror("stat");
        return 1;
    }

    printf("File name : %s\n", argv[1]);
    printf("Size      : %ld bytes\n", fileStat.st_size);

    if (S_ISREG(fileStat.st_mode))
    {
        printf("Type      : Regular file\n");
    }
    else if (S_ISDIR(fileStat.st_mode))
    {
        printf("Type      : Directory\n");
    }
    else
    {
        printf("Type      : Other\n");
    }

    return 0;
}

