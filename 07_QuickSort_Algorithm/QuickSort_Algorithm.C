#include <stdio.h>
#include <stdlib.h>

void quicksort(int *a, int left, int right);

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Uso: %s archivo_entrada archivo_salida\n", argv[0]);
        return 1;
    }

    // Abrir el archivo de entrada
    FILE *in_file = fopen(argv[1], "r");
    if (!in_file) {
        printf("No se pudo abrir el archivo de entrada\n");
        return 1;
    }

    // Contar el número de elementos en el archivo de entrada
    int n = 0, x;
    while (fscanf(in_file, "%d", &x) != EOF) {
        n++;
    }

    // Cerrar y volver a abrir el archivo de entrada
    fclose(in_file);
    in_file = fopen(argv[1], "r");

    // Leer los números del archivo de entrada y guardarlos en un arreglo
    int *a = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        fscanf(in_file, "%d", &a[i]);
    }

    // Ordenar el arreglo con QuickSort
    quicksort(a, 0, n - 1);
    // Escribir los números ordenados en el archivo de salida
    FILE *out_file = fopen(argv[2], "w");
    for (int i = 0; i < n; i++) {
        fprintf(out_file, "%d ", a[i]);
    }
    // Cerrar los archivos y liberar memoria
    fclose(in_file);
    fclose(out_file);
    free(a);
    return 0;
}

void quicksort(int *a, int left, int right) {
    if (left < right) {
        int pivot = a[right];
        int i = left - 1;
        for (int j = left; j < right; j++) {
            if (a[j] <= pivot) {
                i++;   
                int temp = a[i];
                a[i] = a[j];
                a[j] = temp;
            }
        }
        int temp = a[i+1];
        a[i+1] = a[right];
        a[right] = temp;
        quicksort(a, left, i);
        quicksort(a, i+2, right);
    }
}