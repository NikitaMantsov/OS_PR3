#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

double generateRandomNumber(double min, double max) {
    return min + ((double)rand() / RAND_MAX) * (max - min);
}

double calculateAverage(double arr[], int n) {
    double sum = 0.0;
    for (int i = 0; i < n; i++) {
        sum += arr[i];
    }
    return sum / n;
}

int countElementsGreaterThanAverage(double arr[], int n, double average) {
    int count = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i] > average) {
            count++;
        }
    }
    return count;
}

double sumAbsoluteValuesAfterFirstNegative(double arr[], int n) {
    double sum = 0.0;
    int negative_found = 0;

    for (int i = 0; i < n; i++) {
        if (negative_found) {
            sum += fabs(arr[i]);
        }
        if (arr[i] < 0) {
            negative_found = 1;
        }
    }

    return sum;
}

int main() {
    int n;

    srand(time(NULL));

    printf("Enter the number of elements: ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("Invalid input. Number of elements should be positive.\n");
        return 1;
    }

    double arr[n];

    printf("Generated %d random real numbers:\n", n);
    for (int i = 0; i < n; i++) {
        arr[i] = generateRandomNumber(-10.0, 10.0);
        printf("%.2lf ", arr[i]);
    }
    printf("\n");

    double average = calculateAverage(arr, n);

    int count = countElementsGreaterThanAverage(arr, n, average);

    double sum = sumAbsoluteValuesAfterFirstNegative(arr, n);

    printf("Average value: %.2lf\n", average);
    printf("Count of elements greater than the average: %d\n", count);
    printf("Sum of absolute values of elements after the first negative element: %.2lf\n", sum);

    return 0;
}
