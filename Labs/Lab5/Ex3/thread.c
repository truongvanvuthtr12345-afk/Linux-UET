#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

void *square(void *arg)
{
    int n = *(int *)arg;
    printf("Square of %d = %d\n", n, n * n);
    return NULL;
}

int main(void)
{
    pthread_t threads[3];
    int numbers[3] = {5, 10, 15};

    for (int i = 0; i < 3; i++)
    {
        if (pthread_create(&threads[i], NULL, square, &numbers[i]) != 0)
        {
            perror("pthread_create");
            return 1;
        }
    }

    for (int i = 0; i < 3; i++)
    {
        pthread_join(threads[i], NULL);
    }

    return 0;
}
