#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <windows.h>

#define st 1
#define fn 9

typedef char* str;
typedef void (*gametable)(int, int);

int isValid(int** arr, int rows, int cols, int row, int col, int num);
void displayField(int** arr, int rows, int cols, int highlightRow, int highlightCol);
void fillRandomCells(int** arr, int rows, int cols, int numFilled);
int solveSudoku(int** arr, int rows, int cols);
void userInput(int** arr, int rows, int cols);



int isValid(int** arr, int rows, int cols, int row, int col, int num) {
    for (int i = 0; i < rows; ++i) {
        if (*(*(arr + i) + col) == num) return 0;
    }
    for (int j = 0; j < cols; ++j) {
        if (*(*(arr + row) + j) == num) return 0;
    }
    int sqrtSize = (int)sqrt(rows);
    int boxRow = row - row % sqrtSize;
    int boxCol = col - col % sqrtSize;
    for (int i = 0; i < sqrtSize; i++) {
        for (int j = 0; j < sqrtSize; j++) {
            if (*(*(arr + i + boxRow) + j + boxCol) == num) return 0;
        }
    }
    return 1;
}

void displayField(int** arr, int rows, int cols, int highlightRow, int highlightCol) {
    printf("\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (i == highlightRow && j == highlightCol) printf("[");
            else printf(" ");
            
            if (*(*(arr + i) + j) == 0) printf(".");
            else printf("%d", *(*(arr + i) + j));
            
            if (i == highlightRow && j == highlightCol) printf("]");
            else printf(" ");
        }
        printf("\n");
    }
}

void fillRandomCells(int** arr, int rows, int cols, int numFilled) {
    int filled = 0;
    while (filled < numFilled) {
        int row = rand() % rows;
        int col = rand() % cols;
        int num = (rand() % rows) + 1;
        if (*(*(arr + row) + col) == 0 && isValid(arr, rows, cols, row, col, num)) {
            *(*(arr + row) + col) = num;
            filled++;
        }
    }
}

int solveSudoku(int** arr, int rows, int cols) {
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            if (*(*(arr + row) + col) == 0) {
                for (int num = 1; num <= rows; num++) {
                    if (isValid(arr, rows, cols, row, col, num)) {
                        *(*(arr + row) + col) = num;
                        system("cls");
                        displayField(arr, rows, cols, -1, -1);
                        Sleep(500);
                        if (solveSudoku(arr, rows, cols)) return 1;
                        *(*(arr + row) + col) = 0;
                    }
                }
                return 0;
            }
        }
    }
    return 1;
}

void userInput(int** arr, int rows, int cols) {
    int currentRow = 0, currentCol = 0;
    int num;
    char command;
    while (1) {
        system("cls");
        displayField(arr, rows, cols, currentRow, currentCol);
        printf("\nUse WASD to move, E to enter number, Q to quit.\n");
        printf("Current cell: [%d][%d]\n", currentRow + 1, currentCol + 1);
        command = getchar();
        if (command == 'q' || command == 'Q') break;
        if (command == 'w' && currentRow > 0) currentRow--;
        if (command == 's' && currentRow < rows - 1) currentRow++;
        if (command == 'a' && currentCol > 0) currentCol--;
        if (command == 'd' && currentCol < cols - 1) currentCol++;
        if (command == 'e' || command == 'E') {
            printf("Enter number (1-%d): ", rows);
            scanf("%d", &num);
            if (num >= 1 && num <= rows && arr[currentRow][currentCol] == 0 && isValid(arr, rows, cols, currentRow, currentCol, num)) {
                arr[currentRow][currentCol] = num;
            } else {
                printf("Invalid number or cell already filled.\n");
                Sleep(1000);
            }
        }
    }
}
