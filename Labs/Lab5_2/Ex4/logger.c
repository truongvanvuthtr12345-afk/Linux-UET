#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <pthread.h>

#define THREAD_COUNT 3
#define LINES 5

int fd;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

typedef struct {
    int id;
} ThreadData;

void write_all(int fd, const char *buf, size_t len)
{
    size_t written = 0;

    while (written < len) {
        ssize_t n = write(fd, buf + written, len - written);

        if (n < 0) {
            perror("write");
            exit(EXIT_FAILURE);
        }

        written += (size_t)n;
    }
}

void *logger(void *arg)
{
    ThreadData *data = (ThreadData *)arg;

    for (int i = 1; i <= LINES; i++) {
        char line[100];
        int len = snprintf(line, sizeof(line),
                           "Thread %d - line %d\n", data->id, i);

        pthread_mutex_lock(&mutex);
        write_all(fd, line, (size_t)len);
        pthread_mutex_unlock(&mutex);
    }

    return NULL;
}

int main(void)
{
    pthread_t threads[THREAD_COUNT];
    ThreadData data[THREAD_COUNT];

    fd = open("log.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        perror("open");
        return 1;
    }

    for (int i = 0; i < THREAD_COUNT; i++) {
        data[i].id = i + 1;

        if (pthread_create(&threads[i], NULL, logger, &data[i]) != 0) {
            perror("pthread_create");
            return 1;
        }
    }

    for (int i = 0; i < THREAD_COUNT; i++) {
        pthread_join(threads[i], NULL);
    }

    close(fd);
    pthread_mutex_destroy(&mutex);

    fd = open("log.txt", O_RDONLY);
    if (fd == -1) {
        perror("open read");
        return 1;
    }

    char buf[1024];
    ssize_t n;
    int lines = 0;

    while ((n = read(fd, buf, sizeof(buf))) > 0) {
        write(STDOUT_FILENO, buf, (size_t)n);

        for (ssize_t i = 0; i < n; i++) {
            if (buf[i] == '\n')
                lines++;
        }
    }

    close(fd);
    printf("Total lines: %d\n", lines);

    return lines == 15 ? 0 : 1;
}
