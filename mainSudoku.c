#include "SudokuRls.h"

int main() {
    srand(time(0));
    int rows, cols, op;
    int difficultyMode;

    printf("Choose your game table: Type 1 - 4x4, 2 - 6x6, 3 - 9x9\n");
    scanf("%d", &op);
    if (op == 1) rows = cols = 4;
    else if (op == 2) rows = cols = 6;
    else if (op == 3) rows = cols = 9;

    int** arr = (int**)calloc(rows, sizeof(int*));
    for (int i = 0; i < rows; ++i) arr[i] = (int*)calloc(cols, sizeof(int));

    printf("Choose the difficulty mode: 1 - Nightmare, 2 - Hard, 3 - Easy\n");
    scanf("%d", &difficultyMode);

    fillRandomCells(arr, rows, cols, rows * difficultyMode);

    int mode;
    printf("Choose the game mode:\n1. User's mode \n2. Auto solve\n");
    scanf("%d", &mode);
    if (mode == 1) userInput(arr, rows, cols);
    else if (mode == 2) {
        if (!solveSudoku(arr, rows, cols)) printf("Sudoku puzzle is unsolvable.\n");
        else displayField(arr, rows, cols, -1, -1);
    }

    for (int i = 0; i < rows; ++i) free(*(arr + i));
    free(arr);
    return 0;
}
