#include <stdio.h>
#include <stdlib.h>

// Function to input a matrix from the user
double* input_matrix(int* rows, int* columns, const char* matrix_name) {
    printf("Enter the number of rows for %s: ", matrix_name);
    scanf("%d", rows);
    printf("Enter the number of columns for %s: ", matrix_name);
    scanf("%d", columns);

    if (*rows <= 0 || *columns <= 0) {
        printf("Invalid dimensions for %s.\n", matrix_name);
        return NULL;
    }

    double* matrix = (double*)malloc((*rows) * (*columns) * sizeof(double);

    if (matrix == NULL) {
        printf("Memory allocation failed for %s.\n", matrix_name);
        return NULL;
    }

    printf("Enter values for %s (row-major order):\n", matrix_name);
    for (int i = 0; i < (*rows); i++) {
        for (int j = 0; j < (*columns); j++) {
            printf("%s[%d][%d]: ", matrix_name, i, j);
            scanf("%lf", &matrix[i * (*columns) + j]);
        }
    }

    return matrix;
}

// Function to multiply two matrices
int matrix_multiply(const double* matrix1, int rows1, int columns1, const double* matrix2, int rows2, int columns2, double* result) {
    if (columns1 != rows2) {
        printf("Matrix dimensions are not suitable for multiplication.\n");
        return 0;
    }

    for (int i = 0; i < rows1; i++) {
        for (int j = 0; j < columns2; j++) {
            result[i * columns2 + j] = 0;
            for (int k = 0; k < columns1; k++) {
                result[i * columns2 + j] += matrix1[i * columns1 + k] * matrix2[k * columns2 + j];
            }
        }
    }

    return 1;
}

// Function to output a matrix
void output_matrix(const double* matrix, int rows, int columns) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            printf("%.2lf\t", matrix[i * columns + j]);
        }
        printf("\n");
    }
}

int main(void) {
    double* m1;
    double* m2;
    double* m3;
    int m1_rows, m1_columns;
    int m2_rows, m2_columns;

    if (((m1 = input_matrix(&m1_rows, &m1_columns, "Matrix 1")) != NULL) &&
        ((m2 = input_matrix(&m2_rows, &m2_columns, "Matrix 2")) != NULL) &&
        ((m3 = malloc(m1_rows * m2_columns * sizeof(double))) != NULL)) {
        printf("Matrix 1\n");
        output_matrix(m1, m1_rows, m1_columns);
        printf("Matrix 2\n");
        output_matrix(m2, m2_rows, m2_columns);
        if (matrix_multiply(m1, m1_rows, m1_columns, m2, m2_rows, m2_columns, m3)) {
            printf("Product\n");
            output_matrix(m3, m1_rows, m2_columns);
            free(m1);
            free(m2);
            free(m3);
            return 0;
        } else {
            printf("Error in dimensions\n");
            free(m1);
            free(m2);
            free(m3);
            return -1;
        }
    } else {
        free(m1);
        free(m2);
        free(m3);
        printf("Error allocating memory\n");
        return -2;
    }
}

