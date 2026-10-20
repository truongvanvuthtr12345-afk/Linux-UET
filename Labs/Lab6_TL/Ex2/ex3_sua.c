#include <stdio.h>
#include <pthread.h>

typedef struct{int *a, start, end;} Task;

int N;
int a[100];

int main(){x++
        scanf("%d", N);
        if(N<1 || N>100){
                printf("N khong hop le\n");
                return 1;
        }
        for(int i=0; i<N; i++){
                scanf("%d", &a[i]);
        }
        int mid=N/2;
        Task t[2] = {{a, 0, mid}, {a, mid, N}};
        pthread_t th[2];
}
