#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

long long counter, m;
int use_mutex;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void *worker(void *arg){
        for (long long i = 0; i < m; i++) {
                if (use_mutex) pthread_mutex_lock(&lock);
                counter++;
                if (use_mutex) pthread_mutex_unlock(&lock);
        }
        return NULL;
}

int main(int argc, char *argv[]){
        int n = atoi(argv[1]);
        m = atoll(argv[2]);
        pthread_t t[n];

        for (use_mutex = 0; use_mutex <= 1; use_mutex++) {
                counter = 0;
                for (int i = 0; i < n; i++) pthread_create(&t[i], NULL, worker, NULL);
                for (int i = 0; i < n; i++) pthread_join(t[i], NULL);
                printf("%s: %lld (mong doi %lld)\n",
                       use_mutex ? "Co mutex" : "Khong mutex", counter, n * m);
        }
        return 0;
}
