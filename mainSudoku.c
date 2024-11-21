// Import library
#include "SudokuRls.h"


#define MODE 1


int main() {
    srand(time(0));
    int size, op;
    int difficultyMode;
    int mode;
    
    printf("Choose your game table: Type 1 - 4x4, 2 - 9x9\n");
    scanf("%d", &op);
    if (op == 1) size = 4;
    else if (op == 2) size = 9;

    // Allocating memory
    int** arr = (int**)calloc(size, sizeof(int*));
    for (int i = 0; i < size; ++i) arr[i] = (int*)calloc(size, sizeof(int));

    printf("Choose the difficulty mode: 1 - Nightmare, 2 - Hard, 3 - Easy\n");
    scanf("%d", &difficultyMode);

    // Function call to fill first cells on gametable
    fillRandomCells(arr, size, size * difficultyMode);

    #if MODE==1
        userInput(arr, size); // Function call to start user's mode
    
    #elif MODE==0
        if (!solveSudoku(arr, size)) // Autosolver tricky call 
            printf("Sudoku puzzle is unsolvable.\n");
        else {
            displayField(arr, size, -1, -1);
            printf("Easy for computer!");
        }
    #endif
    // Freeing up memory
    for (int i = 0; i < size; ++i) 
        free(*(arr + i));
    free(arr);
    return 0;
}

