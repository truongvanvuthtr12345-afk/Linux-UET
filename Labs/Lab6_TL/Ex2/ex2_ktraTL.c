#include <stdio.h>
#include <pthread.h>

int a[100], n, r[2];

void *count(void *arg) {
    int id = *(int *)arg;
    int start = id * (n / 2);
    int end = (id == 0) ? n / 2 : n;

    r[id] = 0;
    for (int i = start; i < end; i++)
        if (a[i] > 0) r[id]++;
    return NULL;
}

int main() {
	for( 
