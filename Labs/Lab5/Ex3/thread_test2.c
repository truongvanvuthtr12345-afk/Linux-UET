#include <stdio.h>
#include <pthread.h>

void *worker(void *arg){
        int bp=*(int *)arg;
        printf("Binh phuong la: %d\n", bp*bp);
        return NULL;
}

int main(){
        pthread_t tid[3];
        int a[3]={5,10,15};
        for(int i=0; i<3; i++){
                pthread_create(&tid[i], NULL, worker, &a[i]);
        }
        for(int i=0; i<=2; i++){
                pthread_join(tid[i], NULL);
        }
        return 0;
}
