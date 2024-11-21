// Import necessary libraries
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <windows.h>

#define st 1
#define fn 9

#ifndef SUDOKU_H
#define SUDOKU_H
#endif


// Checks the num's possibility of being in gametable
int isValid(int** arr, int size, int row, int col, int num) {
    for (int i = 0; i < size; ++i) {
        if (*(*(arr + i) + col) == num) // searching for dublicates in rows
            return 0;
    }
    for (int j = 0; j < size; ++j) {
        if (*(*(arr + row) + j) == num) // searching for dublicates in rows
            return 0;
    }
    int sqrtSize = (int)sqrt(size);
    int boxRow = row - row % sqrtSize;
    int boxCol = col - col % sqrtSize; 
    for (int i = 0; i < sqrtSize; i++) {
        for (int j = 0; j < sqrtSize; j++) {
            if (*(*(arr + i + boxRow) + j + boxCol) == num) // searching for dublicates in squares
                return 0;
        }
    }
    return 1;
}

// Function is generating gametable 
void displayField(int** arr, int size, int chosenRow, int chosenCol) {
    printf("\n");
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (i == chosenRow && j == chosenCol) 
                printf("[");
            else 
                printf(" ");
            
            if (*(*(arr + i) + j) == 0) 
                printf(".");
            else 
                printf("%d", *(*(arr + i) + j));
            
            if (i == chosenRow && j == chosenCol) 
                printf("]");
            else 
                printf(" ");
        }
        printf("\n");
    }
}
// Fills the gametable with the first numbers
void fillRandomCells(int** arr, int size, int numFilled) {
    int filled = 0;
    while (filled < numFilled) {
        int row = rand() % size;
        int col = rand() % size;
        int num = (rand() % size) + 1;
        if (*(*(arr + row) + col) == 0 && isValid(arr, size, row, col, num)) {
            *(*(arr + row) + col) = num;
            filled++;
        }
    }
}

// Checks if all cells are filled (user's mode)
int isFilled(int** arr, int size){
    for (int i=0;i<size;++i){
        for (int j=0;j<size;++j){
            if (*(*(arr+i)+j)==0)
                return 0;
        }
    }
    return 1;
    
}

// Bruteforce for autosolve mode
int solveSudoku(int** arr, int size) {
    for (int row = 0; row < size; row++) {
        for (int col = 0; col < size; col++) {
            if (*(*(arr + row) + col) == 0) {
                for (int num = 1; num <= size; num++) {
                    if (isValid(arr, size, row, col, num)) {
                        *(*(arr + row) + col) = num;
                        system("cls");
                        displayField(arr, size, -1, -1);
                        Sleep(100);
                        if (solveSudoku(arr, size)) 
                            return 1;
                        *(*(arr + row) + col) = 0;
                    }
                }
                return 0;
            }
        }
    }
    return 1;
}

// Defines user's mode
void userInput(int** arr, int size) {
    int currentRow = 0, currentCol = 0;
    int num;
    char command;
    while (1) {
        if (isFilled(arr,size)==1){
            system("cls");
            displayField(arr,size,-1,-1);
            printf("Win! Congratulations!!!");
            break;
        }
        system("cls");
        displayField(arr, size, currentRow, currentCol);
        printf("\nUse WASD to move, E to enter number, Q to quit.\n");
        printf("Current cell: [%d][%d]\n", currentRow + 1, currentCol + 1);
        command = getch();
        if (command == 'q' || command == 'Q') 
            break;
        if (command == 'w' && currentRow > 0) 
            currentRow--;
        if (command == 's' && currentRow < size - 1) 
            currentRow++;
        if (command == 'a' && currentCol > 0) 
            currentCol--;
        if (command == 'd' && currentCol < size - 1) 
            currentCol++;
        if (command == 'e' || command == 'E') {
            printf("Enter number (1-%d): ", size);
            scanf("%d", &num);
            if (num >= 1 && num <= size && *(*(arr+currentRow)+currentCol) == 0 && isValid(arr, size, currentRow, currentCol, num)) {
                *(*(arr+currentRow)+currentCol)  = num;
            } else {
                printf("Invalid number or cell already filled.\n"); 
                Sleep(1000);
            }
        }
    }
}


