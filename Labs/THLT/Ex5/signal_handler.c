#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void handle_sigint(int sig)
{
    printf("\nSIGINT received\n");
}

int main(void)
{
    signal(SIGINT, handle_sigint);

    while (1)
    {
        printf("Program is running...\n");
        sleep(2);
    }

    return 0;
}

