/**
	Cristian Steven Perafan Monroy - 1625690
	Valeria Rivera - 1626837
	Walter Santacruz - 1630645
******************************************************************************/

#include <stdio.h>
#include <pthread.h>
#include <math.h>

#include <stdint.h>

#define MAXRECT 1000000
#define MAXTHREAD 10
#define BASE 0.0
#define LIMIT 1.0

double length = LIMIT - BASE; // La longitud en el eje 'x'
double numRectxThread = (double)(MAXRECT/MAXTHREAD); // Cuantos hilos/rectangulo
double base_length = 0; // Variable que tiene el ancho de cada rectangulo
double sumTotal = 0; // Variable que tendra la suma total
double partialSums[MAXTHREAD]; // Variable que tien la suma parcial de c/hilo

// Funcion a la que se le calculara la integral, x^2
double function(double x) {
	return x * x; 
}
void* calcular(void *arg) {
	
	int id = (intptr_t)arg;
	
	double loslimit = id*base_length*numRectxThread;
	
	partialSums[id]= 0;
	// 4- Escriba un ciclo que debe recorrer el segmento de 'x' que le 
	//    corresponde a este hilo y donde calcula el area de los rectangulos
    //    que se encuentran en este segmento. Recuerde que la variable
	//    'numRectxThread' contiene el numero de rectangulos que debe
    //    procesar cada hilo.
    for (int i = 0; i < numRectxThread; i++) {
	
	// 5- El area de cada rectangulo se calcula con 
	//    'function(val) * base_length'
		
		partialSums[id] += (double)function(loslimit + i*base_length) * base_length;
	}

	printf("sum: %lf\n", partialSums[id]);
	pthread_exit(NULL);
}

int main(int argc, char** argv) {

	pthread_t threads[MAXTHREAD];
	int taskids[MAXTHREAD];

	base_length = length/MAXRECT; // esta variable contiene el ancho de
				      // cada base de cada rectangulo
	printf("base length: %lf numRectxThread: %lf\n",base_length, numRectxThread);
	// Creacion de los hilos que calcularan el area bajo la curva
	for (int i = 0; i < MAXTHREAD; i++) {
		taskids[i] = i;
		// Inserte la linea de codigo para crear los hilos, los 
		// argumentos son: 
		// - threads
		// - NULL
		// - calcular
		// - taskids
		pthread_create(&threads[i], NULL, calcular, (void*)(intptr_t)taskids[i]);
	}
	
	
	// Ciclo donde se espera el resultado de cada hilo
	for (int i = 0; i < MAXTHREAD; i++) {
		// Inserte la funcion que espera por la terminacion de un hilo.
		// Esta funcion recibe dos argumentos
		// - threads
		// - NULL
		
		pthread_join(threads[i], NULL);
		
		sumTotal += partialSums[i];
	}
	printf("Suma total %lf\n",sumTotal);
	pthread_exit(NULL);
}