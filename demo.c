#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

void main(){
        int status;
        int child_pid=fork();
        if(child_pid){
                waitpid(child_pid, &status, 0);
                printf("I am the parent\n");
        }
        else
                printf("I am the child\n");
}
