#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 1000       // taille du tableau
#define NBFOIS 1000  // nombre de répétitions pour lisser le temps

// ----------- Tri à bulles -----------
void bubble_sort(int arr[], int n) {
    int i, j, temp;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// ----------- Tri par insertion -----------
void insertion_sort(int arr[], int n) {
    int i, j, key;
    for (i = 1; i < n; i++) {
        key = arr[i];
        j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// ----------- Tri par sélection -----------
void selection_sort(int arr[], int n) {
    int i, j, min_idx, temp;
    for (i = 0; i < n - 1; i++) {
        min_idx = i;
        for (j = i + 1; j < n; j++) {
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }
        temp = arr[i];
        arr[i] = arr[min_idx];
        arr[min_idx] = temp;
    }
}

// ----------- Mesure du temps d'un tri -----------
double measure_time(void (*sort_func)(int[], int), int arr[], int n) {
    clock_t start, end;
    int *copy = malloc(n * sizeof(int));

    start = clock();
    for (int k = 0; k < NBFOIS; k++) {
        // recopier le tableau original
        for (int i = 0; i < n; i++) copy[i] = arr[i];
        sort_func(copy, n);
    }
    end = clock();

    free(copy);

    return ((double)(end - start)) / CLOCKS_PER_SEC;
}

int main() {
    srand(time(NULL));

    int arr[N];
    for (int i = 0; i < N; i++) {
        arr[i] = rand() % 10000;  // valeurs aléatoires
    }

    double t_bubble = measure_time(bubble_sort, arr, N);
    double t_insertion = measure_time(insertion_sort, arr, N);
    double t_selection = measure_time(selection_sort, arr, N);

    printf("Temps tri à bulles    : %lf sec\n", t_bubble);
    printf("Temps tri insertion   : %lf sec\n", t_insertion);
    printf("Temps tri selection   : %lf sec\n", t_selection);

    return 0;
}
