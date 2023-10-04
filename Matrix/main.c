#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int rows;
    int cols;
    int** data;
} Matrix;

void initializeMatrix(Matrix* matrix, int rows, int cols) {
    matrix->rows = rows;
    matrix->cols = cols;
    matrix->data = (int**)malloc(rows * sizeof(int*));

    for (int i = 0; i < rows; i++) {
        matrix->data[i] = (int*)malloc(cols * sizeof(int));
        for (int j = 0; j < cols; j++) {
            matrix->data[i][j] = 0;
        }
    }
}

void freeMatrix(Matrix* matrix) {
    for (int i = 0; i < matrix->rows; i++) {
        free(matrix->data[i]);
    }
    free(matrix->data);
}
int rows(Matrix *matrix) {
    return matrix->rows;
}
int cols(Matrix *matrix){
    return matrix->cols;
}

void resizeMatrix(Matrix* matrix, int newRows, int newCols) {
    if (newRows == matrix->rows && newCols == matrix->cols) {
        return;
    }

    int** newData = (int**)malloc(newRows * sizeof(int*));
    for (int i = 0; i < newRows; i++) {
        newData[i] = (int*)malloc(newCols * sizeof(int));
    }

    for (int i = 0; i < newRows; i++) {
        for (int j = 0; j < newCols; j++) {
            if (i < matrix->rows && j < matrix->cols) {
                newData[i][j] = matrix->data[i][j];
            } else {
                newData[i][j] = 0;
            }
        }
    }

    for (int i = 0; i < matrix->rows; i++) {
        free(matrix->data[i]);
    }
    free(matrix->data);

    matrix->rows = newRows;
    matrix->cols = newCols;
    matrix->data = newData;
}

void setElement(Matrix* matrix, int row, int col, int value) {
    if (row < 0 || row >= matrix->rows || col < 0 || col >= matrix->cols) {
        printf("Invalid index.\n");
        return;
    }
    matrix->data[row][col] = value;
}

int getElement(Matrix* matrix, int row, int col) {
    if (row < 0 || row >= matrix->rows || col < 0 || col >= matrix->cols) {
        printf("Invalid index.\n");
        return -1;
    }
    return matrix->data[row][col];
}

void printMatrix(Matrix* matrix) {
    for (int i = 0; i < matrix->rows; i++) {
        for (int j = 0; j < matrix->cols; j++) {
            printf("%d ", matrix->data[i][j]);
        }
        printf("\n");
    }
}

void saveMatrixToFile(Matrix* matrix, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    fprintf(file, "%d %d\n", matrix->rows, matrix->cols);

    for (int i = 0; i < matrix->rows; i++) {
        for (int j = 0; j < matrix->cols; j++) {
            fprintf(file, "%d ", matrix->data[i][j]);
        }
        fprintf(file, "\n");
    }

    fclose(file);
}

void readMatrixFromFile(Matrix* matrix, const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    int rows, cols;
    fscanf(file, "%d %d", &rows, &cols);

    initializeMatrix(matrix, rows, cols);

    for (int i = 0; i < matrix->rows; i++) {
        for (int j = 0; j < matrix->cols; j++) {
            fscanf(file, "%d", &matrix->data[i][j]);
        }
    }

    fclose(file);
}

Matrix addMatrices(Matrix* A, Matrix* B) {
    if (A->rows != B->rows || A->cols != B->cols) {
        printf("The addition operation cannot be performed: the matrices are of different size.\n");
        Matrix emptyMatrix;
        initializeMatrix(&emptyMatrix, 0, 0);
        return emptyMatrix;
    }

    Matrix result;
    initializeMatrix(&result, A->rows, A->cols);

    for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->cols; j++) {
            result.data[i][j] = A->data[i][j] + B->data[i][j];
        }
    }

    return result;
}

Matrix subtractMatrices(Matrix* A, Matrix* B) {
    if (A->rows != B->rows || A->cols != B->cols) {
        printf("Subtraction cannot be performed: matrices are of different size.\n");
        Matrix emptyMatrix;
        initializeMatrix(&emptyMatrix, 0, 0);
        return emptyMatrix;
    }

    Matrix result;
    initializeMatrix(&result, A->rows, A->cols);

    for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->cols; j++) {
            result.data[i][j] = A->data[i][j] - B->data[i][j];
        }
    }

    return result;
}

Matrix multiplyMatrixByScalar(Matrix* matrix, int scalar) {
    Matrix result;
    initializeMatrix(&result, matrix->rows, matrix->cols);

    for (int i = 0; i < matrix->rows; i++) {
        for (int j = 0; j < matrix->cols; j++) {
            result.data[i][j] = matrix->data[i][j] * scalar;
        }
    }

    return result;
}

Matrix multiplyMatrices(Matrix* A, Matrix* B) {
    if (A->cols != B->rows) {
        printf("Unable to perform multiplication operation: wrong matrix size.\n");
        Matrix emptyMatrix;
        initializeMatrix(&emptyMatrix, 0, 0);
        return emptyMatrix;
    }

    Matrix result;
    initializeMatrix(&result, A->rows, B->cols);

    for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < B->cols; j++) {
            result.data[i][j] = 0;
            for (int k = 0; k < A->cols; k++) {
                result.data[i][j] += A->data[i][k] * B->data[k][j];
            }
        }
    }

    return result;
}

int main() {
    Matrix matrixA, matrixB;
    initializeMatrix(&matrixA, 3, 3);
    initializeMatrix(&matrixB, 3, 3);

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            setElement(&matrixA, i, j, i + j);
            setElement(&matrixB, i, j, i - j);
        }
    }

    printf("Matrix A:\n");
    printMatrix(&matrixA);

    printf("Rows matrix A: %d\n", rows(&matrixA));
    printf("Cols matrix A: %d\n", cols(&matrixA));
    printf("Element from matrix A 0, 2: %d\n", getElement(&matrixA,0,2));

    printf("Matrix B:\n");
    printMatrix(&matrixB);

    Matrix sum = addMatrices(&matrixA, &matrixB);
    printf("--- A + B ---\n");
    printMatrix(&sum);
    freeMatrix(&sum);

    Matrix difference = subtractMatrices(&matrixA, &matrixB);
    printf("--- A - B ---\n");
    printMatrix(&difference);
    freeMatrix(&difference);

    Matrix scaled = multiplyMatrixByScalar(&matrixA, 2);
    printf("--- A * 2 ---\n");
    printMatrix(&scaled);
    freeMatrix(&scaled);

    Matrix product = multiplyMatrices(&matrixA, &matrixB);
    printf("--- A * B ---\n");
    printMatrix(&product);
    freeMatrix(&product);

    saveMatrixToFile(&matrixA, "matrixA.txt");
    Matrix loadedMatrix;
    readMatrixFromFile(&loadedMatrix, "matrixA.txt");
    printf("Matrix A from file:\n");
    printMatrix(&loadedMatrix);
    freeMatrix(&loadedMatrix);
    printf("Matrix A after resize:\n");
    resizeMatrix(&matrixA,4,4);
    printMatrix(&matrixA);

    freeMatrix(&matrixA);
    freeMatrix(&matrixB);

    return 0;
}
