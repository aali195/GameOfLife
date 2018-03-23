/* Program that simulates the game "Game of Life".
 * First, takes 3 inputs, rows, columns and number of steps/generations
 * Then takes the initial board state
 * Returns the board state of the final generation/step
 */

#include <stdio.h>
#include <stdlib.h>

/*
 * Constants for alive and dead cells, can be changed
 */
#define ALIVE 'X'
#define DEAD '.'

/*
 * Initialises the board with the user input
 * Takes the number of rows and columns as well as the board pointer
 * Sets the board position to be user's input if it passes a conditional statement
 */
void initialiseBoard(int rows, int cols, char **board) {
    char tempChar;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            scanf(" %c", &tempChar);
            /* Checks to see if the user input format is correct before assigning to board
             *  closes the program if not
             *  */
            if (tempChar == ALIVE || tempChar == DEAD) {
                board[i][j] = tempChar;
            } else {
                printf("Error. Board value must be '%c' or '%c'.\n", ALIVE, DEAD);
                exit(1);
            }
        }
    }
}

/*
 * Method used to check a cell's value
 * Takes the working row and column, total rows and columns as well as the board
 * Returns 0 if the cell is dead or out of bounds
 * Returns 1 if the cell is alive
 */
int getNeighbourValue(int row, int col, int rows, int cols, char **board) {
    if (row < 0 || row >= rows || col < 0 || col >= cols || board[row][col] != ALIVE) {
        return 0;
    }
    else {
        return 1;
    }
}

/*
 * Method that counts the number of alive neighbouring cells
 * Takes the working row and column, total rows and columns as well as the board
 * Returns the total count
 */
int getNeighbourCount(int row, int col, int rows, int cols, char **board) {
    int count = 0;
    
    /* Statements used to check each surrounding cell and then adding the value to the counter */
    count += getNeighbourValue(row - 1, col - 1, rows, cols, &*board);
    count += getNeighbourValue(row - 1, col, rows, cols, &*board);
    count += getNeighbourValue(row - 1, col + 1, rows, cols, &*board);
    count += getNeighbourValue(row, col - 1, rows, cols, &*board);
    count += getNeighbourValue(row, col + 1, rows, cols, &*board);
    count += getNeighbourValue(row + 1, col - 1, rows, cols, &*board);
    count += getNeighbourValue(row + 1, col, rows, cols, &*board);
    count += getNeighbourValue(row + 1, col + 1, rows, cols, &*board);
    
    return count;
}

/*
 * Method that writes the new generated board to the original
 * Takes the total rows and cols as well as the original and new boards.
 */
void writeNewGen(int rows, int cols, char **board, char **newBoard) {
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            board[row][col] = newBoard[row][col];
        }
    }
}

/* Prints the results
 * Takes the number of rows and columns as well as board as a char
 * Loop through the board treating it like a matrix and print the content of each cell
 * as a char
 */
void printResult(int rows, int cols, char **board) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%c", board[i][j]);
        }
        printf("\n");
    }
}

/*
 * Method used to run the simulation
 * Takes the total rows and columns, the number of steps desired and the board
 */
void runSimulation(int rows, int cols, int steps, char **board) {
    /* Dynamically allocate a new array of pointers to pointers that will be used for new generations*/
    char **newBoard;
    newBoard = (char **)malloc(rows * sizeof(char *));
    for (int i = 0; i < rows; i++) {
        newBoard[i] = (char *)malloc(cols * sizeof(char));
    }
    if (newBoard == NULL) {
        printf("Error. Not enough space available.\n");
        exit(1);
    }
    
    /* Loop used to simulate passing generations */
    for(int gen = 0; gen < steps; gen++) {
        int r, c;
        for(r = 0; r < rows; r++) {
            for(c = 0; c < cols; c++) {
                /* Variable used to call the function that counts the total number of alive neighbours and stores it */
                int neighbourCount = getNeighbourCount(r, c, rows, cols, &*board);
                
                /* Check the count with the rules of the game and set the value on the new board*/
                if(neighbourCount == 3) {
                    newBoard[r][c] = ALIVE;
                } else if(neighbourCount == 2 && board[r][c] == ALIVE) {
                    newBoard[r][c] = ALIVE;
                } else {
                    newBoard[r][c] = DEAD;
                }
            }
        }
        /* Write the new board state to the original after a generation passes */
        writeNewGen(rows, cols, &*board, &*newBoard);
    }
    
    /* Free the memory space used for the new board */
    free(newBoard);
    
}

/* Main function to take input and call the simulation and printing */
int main() {
    /* Taking the initial input line */
    int rows, cols, steps;
    scanf("%d %d %d", &rows, &cols, &steps);
    if (rows <= 0 || cols <= 0) {
        printf("Error. Rows and columns must be larger than 0.\n");
        exit(1);
    }
    
    /* Dynamically allocate an array of pointers to pointers that will be used as the game board*/
    char **board;
    board = (char **)malloc(rows * sizeof(char *));
    for (int i = 0; i < rows; i++) {
        board[i] = (char *)malloc(cols * sizeof(char));
    }
    /* Check to see if memory space was given, if not then exist */
    if (board == NULL) {
        printf("Error. Not enough space available.\n");
        exit(1);
    }
    
    /* Calls for the functions responsible for the initialisation, simulation and priting */
    initialiseBoard(rows, cols, &*board);
    runSimulation(rows, cols, steps, &*board);
    printResult(rows, cols, &*board);
    
    /* Free the memory space used for the board */
    free(board);
    return 0;
}
