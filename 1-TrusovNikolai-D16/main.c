#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include"pentomino.h"
int** fillField() {
    int** field;
    FILE* f;
    int value;
    int M;
    int N;
    if ((f = fopen("input.txt", "rb")) == NULL)
        printf("The file 'input.txt' was not opened\n");
    fscanf(f, "%d", &M);
    fscanf(f, "%d", &N);
    field = (int**)calloc(M, sizeof(int*));
    if (!field) {
        printf("Error allocating memory\n");
        exit(1);
    }
    for (int i = 0; i < M; i++) {
        field[i] = (int*)calloc(N, sizeof(int));
        if (!field[i]) {
            printf("Error allocating memory\n");
            exit(1);
        }
    }

    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            fscanf(f, "%d", &value);
            field[i][j] = value;
        }
    }
    fclose(f);
    return field;
}
int isInserted(int** field, int x, int y, int numShape, int numPiece, int M, int N) {
    int flag = TRUE;
    if (x + Shapes[numShape].Pieces[numPiece].right >= N) {
        flag = FALSE;
    }
    if (x - Shapes[numShape].Pieces[numPiece].left < 0) {
        flag = FALSE;
    }
    if (y + Shapes[numShape].Pieces[numPiece].below >= M) {
        flag = FALSE;
    }
    if (flag == FALSE) {
        return flag;
    }
    for (int i = 0; i < Shapes[numShape].Pieces[numPiece].below + 1; i++) {
        for (int j = 0; j < Shapes[numShape].Pieces[numPiece].right + Shapes[numShape].Pieces[numPiece].left + 1; j++) {
            if (Shapes[numShape].Pieces[numPiece].Arr[i][j] != 0) {
                if (field[y + i][x + j - Shapes[numShape].Pieces[numPiece].left] != 1) {
                    flag = FALSE;
                    return flag;
                }
            }
        }
    }
    return flag;
}
void insert(int** field, int x, int y, int numShape, int numPiece) {
    for (int i = 0; i < Shapes[numShape].Pieces[numPiece].below + 1; i++) {
        for (int j = 0; j < Shapes[numShape].Pieces[numPiece].right + Shapes[numShape].Pieces[numPiece].left + 1; j++) {
            if (Shapes[numShape].Pieces[numPiece].Arr[i][j] != 0) {
                field[y + i][x + j - Shapes[numShape].Pieces[numPiece].left] = Shapes[numShape].Pieces[numPiece].Arr[i][j];
            }
        }
    }
}
int** cpyArr(int** src, int M, int N) {
    int** dst;
    dst = (int**)calloc(M, sizeof(int*));
    if (!dst) {
        printf("Error allocating memory\n");
        exit(1);
    }
    for (int i = 0; i < M; i++) {
        dst[i] = (int*)calloc(N, sizeof(int));
    }
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            if (!dst[i]) {
                printf("Error allocating memory\n");
                exit(1);
            }
            dst[i][j] = src[i][j];
        }
    }
    return dst;
}
void free_matrix(int** matrix, int N) {
    for (int i = 0; i < N; i++) {
        free(matrix[i]);
    }
    free(matrix);
}
void printField(int** field, int M, int N) {
    FILE* f;
    if ((f = fopen("output.txt", "wb")) == NULL)
        printf("The file 'output.txt' was not opened\n");
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            switch (field[i][j]) {
            case 2:
                fprintf(f, "P");
                break;
            case 3:
                fprintf(f, "I");
                break;
            case 4:
                fprintf(f, "V");
                break;
            case 5:
                fprintf(f, "W");
                break;
            case 6:
                fprintf(f, "T");
                break;
            case 7:
                fprintf(f, "U");
                break;
            case 8:
                fprintf(f, "F");
                break;
            case 9:
                fprintf(f, "L");
                break;
            case 10:
                fprintf(f, "Y");
                break;
            case 11:
                fprintf(f, "N");
                break;
            case 12:
                fprintf(f, "X");
                break;
            case 13:
                fprintf(f, "Z");
                break;
            default:
                fprintf(f, "%d", field[i][j]);
            }
        }
        fprintf(f, "\n");
    }
    fclose(f);
}
int pentomino(int** field, int numFig, int M, int N) {
    int flag = 1;
    int x, y;
    for (y = 0; y < M; y++) {
        for (x = 0; x < N; x++) {
            if (field[y][x] != 1) {
                continue;
            }
            for (int i = 0; i < MAX_SHAPES; i++) {
                for (int j = 0; j < Shapes[i].count; j++) {
                    if (isInserted(field, x, y, i, j, M, N) == TRUE) {
                        insert(field, x, y, i, j);
                        if (numFig + 1 == NUMBER_OF_FIGURES) {
                            printField(field, M, N);
                            return TRUE;
                        }
                        int** A = cpyArr(field, M, N);
                        if (pentomino(A, numFig + 1, M, N) == TRUE) {
                            free_matrix(A, M);
                            return TRUE;
                        }
                        free_matrix(A, M);
                        if (numFig == 0) {
                            free_matrix(field, M);
                            field = fillField();

                        }
                    }
                }
            }
        }
    }
    return FALSE;
}
int main(void) {
    int** field;
    int M;
    int N;
    FILE* f;
    if ((f = fopen("input.txt", "rb")) == NULL)
        printf("The file 'input.txt' was not opened\n");
    fscanf(f, "%d", &M);
    fscanf(f, "%d", &N);
    fclose(f);
    field = fillField();
    if (pentomino(field, 0, M, N) == FALSE) {
        FILE* f;
        if ((f = fopen("output.txt", "wb")) == NULL)
            printf("The file 'output.txt' was not opened\n"); \
            fprintf(f, "-1");
    }
    return 0;

}