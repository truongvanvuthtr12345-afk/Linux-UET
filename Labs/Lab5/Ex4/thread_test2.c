#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *worker(void *arg) {
    int n = *(int *)arg;
    long *tong = malloc(sizeof(long));   // cấp phát trên heap
    *tong = 0;
    for (int i = 1; i <= n; i++)
        *tong += i;
    return tong;                         // trả về con trỏ
}

int main() {
