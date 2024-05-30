#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>

// Estructura para mantener el rango para cada hilo
typedef struct {
    int inicio;
    int fin;
} Rango;

int total_primos=0;

// Función para verificar si un número es primo
int es_primo(int num) {
    if (num <= 1) return 0;
    if (num == 2) return 1;
    if (num % 2 == 0) return 0;
    for (int i = 3; i <= sqrt(num); i += 2) {
        if (num % i == 0) return 0;
 }
    return 1;
}

// Función del hilo para verificar números primos en un rango dado
void* verificar_primo(void* arg) {
    Rango* rango = (Rango*)arg;
    int count=0;
    for (int i = rango->inicio; i <= rango->fin; i++) {
        if (es_primo(i)) {
            count++;
            printf("Hilo %ld: %d es primo\n", pthread_self(), i);
        }
    }
    return (void*)count;
}

int main() {
    int inicio = 1, fin = 100;
    int num_hilos = 4;
    pthread_t hilos[num_hilos];
    Rango rangos[num_hilos];

    // Dividir el rango en partes para cada hilo
    int tamano_rango = (fin - inicio + 1) / num_hilos;
    for (int i = 0; i < num_hilos; i++) {
        rangos[i].inicio = inicio + i * tamano_rango;
        rangos[i].fin = (i == num_hilos - 1) ? fin : (inicio + (i + 1) * tamano_rango - 1);
    }

    // Crear hilos
    for (int i = 0; i < num_hilos; i++) {
        if (pthread_create(&hilos[i], NULL, verificar_primo, &rangos[i]) != 0) {
            perror("Error al crear el hilo");
            return 1;
        }
    }

    // Unir hilos
    for (int i = 0; i < num_hilos; i++) {
        void* parcial;
        pthread_join(hilos[i], &parcial);
        total_primos+=(int) parcial;
        
    }
    printf("total primos:%d",total_primos);
    return 0;
}
