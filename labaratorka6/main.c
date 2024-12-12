#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

void create_random_matrices(int M, int N, double*** matrix1, double*** matrix2)
{
    *matrix1 = (double**)malloc(M * sizeof(double*));
    *matrix2 = (double**)malloc(M * sizeof(double*));

    for (int i = 0; i < M; i++)
    {
        (*matrix1)[i] = (double*)malloc(N * sizeof(double));
        (*matrix2)[i] = (double*)malloc(N * sizeof(double));
    }

    srand(time(NULL)); 

    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            (*matrix1)[i][j] = (double)(rand() % 100) / 10.0; 
            (*matrix2)[i][j] = (double)(rand() % 100) / 10.0;
        }
    }
}

int count_similar_rows_and_columns(double** matrix1, double** matrix2, int M, int N, double eps) {
    int similar_count = 0;

    
    for (int i = 0; i < M; i++) 
    {
        int similar = 1;
        for (int j = 0; j < N; j++)
        {
            if (fabs(matrix1[i][j] - matrix2[i][j]) >= eps)
            {
                similar = 0;
                break;
            }
        }
        if (similar)
        {
            similar_count++;
        }
    }

    for (int j = 0; j < N; j++)
    {
        int similar = 1;
        for (int i = 0; i < M; i++)
        {
            if (fabs(matrix1[i][j] - matrix2[i][j]) >= eps)
            {
                similar = 0;
                break;
            }
        }
        if (similar)
        {
            similar_count++;
        }
    }

    return similar_count;
}

void free_matrices(double** matrix1, double** matrix2, int M) {
    for (int i = 0; i < M; i++) 
    {
        free(matrix1[i]);
        free(matrix2[i]);
    }
    free(matrix1);
    free(matrix2);
}

int main() {
    int M = 3, N = 3;
    double** matrix1, ** matrix2;
    double eps = 0.1;

    create_random_matrices(M, N, &matrix1, &matrix2);

    printf("Matrix 1:\n");
    for (int i = 0; i < M; i++)
    {
        for (int j = 0; j < N; j++)
        {
            printf("%.2f ", matrix1[i][j]);
        }
        printf("\n");
    }

    printf("\nMatrix 2:\n");
    for (int i = 0; i < M; i++) 
    {
        for (int j = 0; j < N; j++) 
        {
            printf("%.2f ", matrix2[i][j]);
        }
        printf("\n");
    }

    int similar_count = count_similar_rows_and_columns(matrix1, matrix2, M, N, eps);
    printf("\nNumber of similar rows and columns: %d\n", similar_count);

    free_matrices(matrix1, matrix2, M);
    return 0;
}