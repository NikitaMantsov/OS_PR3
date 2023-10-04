#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

typedef struct {
    double x, y, z;
    double mass;
} Point;

double distance(Point p1, Point p2) {
    double dx = p1.x - p2.x;
    double dy = p1.y - p2.y;
    double dz = p1.z - p2.z;
    return sqrt(dx * dx + dy * dy + dz * dz);
}

int main() {
    srand(time(NULL));

    int n;
    printf("Enter the number of points: ");
    scanf("%d", &n);

    if (n < 1) {
        printf("Enter a valid number of points.\n");
        return 1;
    }

    Point* points = malloc(n * sizeof(Point));
    for (int i = 0; i < n; i++) {
        points[i].x = (double)rand() / RAND_MAX * 10.0;
        points[i].y = (double)rand() / RAND_MAX * 10.0;
        points[i].z = (double)rand() / RAND_MAX * 10.0;
        points[i].mass = (double)rand() / RAND_MAX * 10.0;
    }

    while (n > 1) {
        printf("Current state of points:\n");
        for (int i = 0; i < n; i++) {
            printf("Point %d: (x=%.2f, y=%.2f, z=%.2f) Mass=%.2f\n",
                   i, points[i].x, points[i].y, points[i].z, points[i].mass);
        }

        int minIndex = 0;
        for (int i = 1; i < n; i++) {
            if (points[i].mass < points[minIndex].mass) {
                minIndex = i;
            }
        }

        double minDistance = -1.0;
        int nearestIndex = -1;
        for (int i = 0; i < n; i++) {
            if (i != minIndex) {
                double dist = distance(points[minIndex], points[i]);
                if (minDistance < 0 || dist < minDistance) {
                    minDistance = dist;
                    nearestIndex = i;
                }
            }
        }

        points[nearestIndex].mass += points[minIndex].mass;
        printf("Point %d transfers its mass to point %d\n", minIndex, nearestIndex);
        points[minIndex] = points[n - 1];
        n--;
    }

    printf("The remaining point has coordinates (x=%.2f, y=%.2f, z=%.2f) and mass %.2f\n",
           points[0].x, points[0].y, points[0].z, points[0].mass);

    free(points);

    return 0;
}