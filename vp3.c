#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>

// Estructura para mantener el rango para cada hilo
typedef struct {
    int inicio;
    int fin;
    int primos;
} Rango;



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
    rango->primos=0;
    for (int i = rango->inicio; i <= rango->fin; i++) {
        if (es_primo(i)) {
            rango->primos++;
           
        }
    }
    return NULL;
}

int sumarVector(int vector[4]){
    int suma=0;
    for(int i=0;i<4;i++){
     suma+=vector[i];
    }
    return suma;

}

int main() {
    int inicio = 1, fin = 100;
    int num_hilos = 4;
    pthread_t hilos[num_hilos];
    Rango rangos[num_hilos];
    int Primos[num_hilos];
    int total_primos=0;

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
        pthread_join(hilos[i],NULL);
        printf("num Primos hilo %d: %d\n",i,rangos[i].primos);
        total_primos+=rangos[i].primos;
        
    }

    printf("total primos %d",total_primos);
    
    return 0;
}

