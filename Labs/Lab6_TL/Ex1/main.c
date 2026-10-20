
#include <stdio.h>
#include <pthread.h>

#define N 12

// Du lieu dung chung: mang chi duoc DOC boi ca hai thread
int arr[N];
// Ket qua rieng cua tung thread (moi bien chi 1 thread ghi)
long sum_result = 0;
int even_result = 0;
// Thread 1: tinh tong
void *compute_sum(void *arg) {
    long s = 0;
    for (int i = 0; i < N; i++)
        s += arr[i];
    sum_result = s;
    return NULL;
}

// Thread 2: dem so chan
void *count_even(void *arg) {
    int c = 0;
    for (int i = 0; i < N; i++)
        if (arr[i] % 2 == 0)
            c++;
    even_result = c;
    return NULL;
}

int main(void) {
    // Buoc 1 (bat buoc chay truoc): nhap mang 12 so
    printf("Nhap %d so nguyen: ", N);
    for (int i = 0; i < N; i++) {
        if (scanf("%d", &arr[i]) != 1) {
            fprintf(stderr, "Du lieu nhap khong hop le\n");
            return 1;
        }
    }

    // Buoc 2 + 3: hai thread chay dong thoi
    pthread_t t_sum, t_even;
    pthread_create(&t_sum, NULL, compute_sum, NULL);
    pthread_create(&t_even, NULL, count_even, NULL);

    // Buoc 4 (chay sau cung): main cho ca hai thread xong roi moi in
    pthread_join(t_sum, NULL);
    pthread_join(t_even, NULL);

    printf("Array:");
    for (int i = 0; i < N; i++)
        printf(" %d", arr[i]);
    printf("\n");
    printf("Sum: %ld; Even: %d\n", sum_result, even_result);

    return 0;
}
