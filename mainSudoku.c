#include "SudokuRls.h"


int main() {
    srand(time(0));
    int size, op;
    int difficultyMode;

    printf("Choose your game table: Type 1 - 4x4, 2 - 9x9\n");
    scanf("%d", &op);
    if (op == 1) size = 4;
    else if (op == 2) size = 9;

    int** arr = (int**)calloc(size, sizeof(int*));
    for (int i = 0; i < size; ++i) arr[i] = (int*)calloc(size, sizeof(int));

    printf("Choose the difficulty mode: 1 - Nightmare, 2 - Hard, 3 - Easy\n");
    scanf("%d", &difficultyMode);

    fillRandomCells(arr, size, size * difficultyMode);

    int mode;
    printf("Choose the game mode:\n1. User's mode \n2. Auto solve\n");
    scanf("%d", &mode);
    if (mode == 1) {
        userInput(arr, size);
        
    }

    else if (mode == 2) {
        if (!solveSudoku(arr, size)) 
            printf("Sudoku puzzle is unsolvable.\n");
        else {
            displayField(arr, size, -1, -1);
            printf("Easy for computer!");
        }
    }

    for (int i = 0; i < size; ++i) 
        free(*(arr + i));
    free(arr);
    return 0;
}
