#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <omp.h>

// Funciones para cargar y guardar imágenes en archivos binarios
void cargarImagen(int *imagen, int width, int height);
void guardarImagen(int *imagen, int width, int height);

// Función para aplicar un filtro de Sobel a una imagen
void aplicarFiltro(int *imagen, int *imagenProcesada, int width, int height);

// Función para calcular la suma de los píxeles de una imagen
int calcularSumaPixeles(int *imagen, int width, int height);

char *filename;

int main(int argc, char* argv[]) {
    // Dimensiones de la imagen (asumimos que es una imagen cuadrada)
    int width = 1024, height = 1024;
    int *imagen = (int *)malloc(width * height * sizeof(int));
    int *imagenProcesada = (int *)malloc(width * height * sizeof(int));

    // Verificar que se ha pasado el nombre del archivo como argumento
    if (argc != 2) {
        fprintf(stderr, "Debe proporcionar un nombre de archivo de entrada\n");
        exit(1);
    }

    filename = argv[1];

    // Cargar la imagen desde un archivo binario (no se paraleliza esta parte)
    cargarImagen(imagen, width, height);

    // Establecer el número de hilos para la ejecución paralela
    int numHilos = 2 * omp_get_num_procs(); // Usamos el doble del número de procesadores
    omp_set_num_threads(numHilos);

    // Aplicar el filtro a la imagen utilizando paralelismo
    aplicarFiltro(imagen, imagenProcesada, width, height);

    // Calcular la suma de los píxeles en la imagen procesada (también se puede paralelizar)
    int sumaPixeles = calcularSumaPixeles(imagenProcesada, width, height);

    printf("Suma de píxeles: %d\n", sumaPixeles);

    // Guardar la imagen procesada en un archivo (no se paraleliza)
    guardarImagen(imagenProcesada, width, height);

    // Liberar la memoria asignada
    free(imagen);
    free(imagenProcesada);

    return 0;
}

// Carga una imagen desde un archivo binario
void cargarImagen(int *imagen, int width, int height) {
    FILE *archivo = fopen(filename, "rb");
    if (archivo == NULL) {
        perror("Error al abrir el archivo para cargar la imagen");
        return;
    }

    size_t elementosLeidos = fread(imagen, sizeof(int), width * height, archivo);
    if (elementosLeidos != width * height) {
        perror("Error al leer la imagen desde el archivo");
    }

    fclose(archivo);
}

// Guarda una imagen procesada en un archivo binario
void guardarImagen(int *imagen, int width, int height) {
    char *output_filename = (char*)malloc(sizeof(char) * (strlen(filename) + 4));
    sprintf(output_filename, "%s.new", filename);
    
    FILE *archivo = fopen(output_filename, "wb");
    if (archivo == NULL) {
        perror("Error al abrir el archivo para guardar la imagen");
        return;
    }

    size_t elementosEscritos = fwrite(imagen, sizeof(int), width * height, archivo);
    if (elementosEscritos != width * height) {
        perror("Error al escribir la imagen en el archivo");
    }

    fclose(archivo);
    free(output_filename);
}

// Aplicar filtro Sobel a la imagen (paralelizable)
void aplicarFiltro(int *imagen, int *imagenProcesada, int width, int height) {
    int Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int Gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    #pragma omp parallel for collapse(2) schedule(static)
    for (int y = 1; y < height - 1; y++) {
        for (int x = 1; x < width - 1; x++) {
            int sumX = 0, sumY = 0;

            // Aplicar las máscaras de Sobel (Gx y Gy)
            for (int ky = -1; ky <= 1; ky++) {
                for (int kx = -1; kx <= 1; kx++) {
                    sumX += imagen[(y + ky) * width + (x + kx)] * Gx[ky + 1][kx + 1];
                    sumY += imagen[(y + ky) * width + (x + kx)] * Gy[ky + 1][kx + 1];
                }
            }

            // Calcular la magnitud del gradiente y normalizar a 8 bits
            int magnitude = abs(sumX) + abs(sumY);
            imagenProcesada[y * width + x] = (magnitude > 255) ? 255 : magnitude;
        }
    }
}

// Sumar todos los píxeles de una imagen
int calcularSumaPixeles(int *imagen, int width, int height) {
    int suma = 0;

    // Sumar los valores de todos los píxeles
    for (int i = 0; i < width * height; i++) {
        suma += imagen[i];
    }

    return suma;
}
