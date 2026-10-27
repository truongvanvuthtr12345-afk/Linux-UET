#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

void *work(void *arg) {
	int id = *(int *)arg;
	printf("Thread %d: Dang lam viec\n", id);
	sleep(1);
	printf("Thread %d: Hoan thanh\n", id);
	return NULL;
}

int main(int argc, char *argv[]) {
	if (argc != 2) {
	printf("Nhap: ./threads 3\n");
	return 1;
	}
	int n = atoi(argv[1]);
	pthread_t t[n];
	int id[n];
	for (int i = 0; i < n; i++) {
	id[i] = i + 1;
	pthread_create(&t[i], NULL, work, &id[i]);
	}
	for (int i = 0; i < n; i++) {
	pthread_join(t[i], NULL);
	}
	printf("Tat ca thread da xong!\n");
	return 0;
}
