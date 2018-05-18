/*

Autor: Valeria Rivera 
Fecha: 17/05/18
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define THREADS 10


void *saludo(void *null) {
	printf("Hola - %ld\n", pthread_self());
	pthread_exit(NULL);
}

int main(int argc, char *argv[]) {

	pthread_t ids[THREADS];

	for (int i = 0; i<THREADS; i++) {
		pthread_create(&ids[i], NULL, saludo, NULL);
	}

	for(int j = 0; j<THREADS; j++) {
		pthread_join(ids[j], NULL);
	}

	return 0;
}     