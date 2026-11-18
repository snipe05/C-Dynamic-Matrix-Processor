#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char nome[100];
    int n;
    int m;
} Parametri;

Parametri readInput(int argc, char* argv[]) {
    Parametri p;
    if (argc != 4) exit(1);

    strcpy(p.nome, argv[1]);
    p.n = atoi(argv[2]);
    p.m = atoi(argv[3]);

    if (p.n < 5 || p.n > 10 || p.m < 5 || p.m > 10) exit(1);
    return p;
}

double*** allocateMatrix(int r, int c) {
    double*** m = malloc(r * sizeof(double**));
    if (!m) exit(1);

    for(int i=0; i<r; i++) {
        m[i] = malloc(c * sizeof(double*));
        if (!m[i]) exit(1);
        for(int j=0; j<c; j++) {
            m[i][j] = malloc(sizeof(double));
            if (!m[i][j]) exit(1);
            *m[i][j] = 0.0;
        }
    }
    return m;
}

void fillMatrix(double*** m, int r, int c, char* file) {
    FILE* fp = fopen(file, "r");
    if (!fp) exit(1);

    for(int i=0; i<r; i++) {
        for(int j=0; j<c; j++) {
            fscanf(fp, "%lf", m[i][j]);
        }
    }
    fclose(fp);
}

void printMatrix(double*** m, int r, int c) {
    for(int i=0; i<r; i++) {
        for(int j=0; j<c; j++) {
            printf("%f ", *m[i][j]);
        }
        printf("\n");
    }
}

void normalize(double*** a, double*** b, int r, int c) {
    for(int j=0; j<c; j++) {
        double max = *a[0][j];
        for(int i=1; i<r; i++) {
            if(*a[i][j] > max) max = *a[i][j];
        }
        for(int i=0; i<r; i++) {
            if(max != 0) *b[i][j] = *a[i][j] / max;
            else *b[i][j] = 0.0;
        }
    }
}

void sortMatrixCols(double*** m, int r, int c) {
    for(int j=0; j<c; j++) {
        for(int i=0; i<r-1; i++) {
            for(int k=0; k<r-i-1; k++) {
                if(*m[k][j] > *m[k+1][j]) {
                    double tmp = *m[k][j];
                    *m[k][j] = *m[k+1][j];
                    *m[k+1][j] = tmp;
                }
            }
        }
    }
}

int main(int argc, char* argv[]) {
    Parametri p = readInput(argc, argv);

    double*** A = allocateMatrix(p.n, p.m);
    fillMatrix(A, p.n, p.m, p.nome);

    double*** B = allocateMatrix(p.n, p.m);
    normalize(A, B, p.n, p.m);

    printf("**A **\n");
    printMatrix(A, p.n, p.m);

    printf("** B **\n");
    printMatrix(B, p.n, p.m);

    sortMatrixCols(B, p.n, p.m);
    printf("** B (sorted columns) **\n");
    printMatrix(B, p.n, p.m);

    return 0;
}