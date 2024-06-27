// Libraries and definitions
#pragma warning(disable : 4996)
#pragma warning(disable : 6031)
#include <stdio.h>
#include <conio.h> // for _getch()

#ifndef __TRUE_FALSE__
#define __TRUE_FALSE__
#define TRUE           1
#define FALSE          0
#endif

// Define player symbols, board size, and empty cell
#define ROWS           7
#define COLS           7
#define MARKONE       'X'
#define MARKTWO       'O'
#define BLANK         ' '

// Return codes for player move outcome
#define CODE_OK         0 // SUCCESS
#define CODE_OOB        1 // OUT OF BOUNDS
#define CODE_COLLISION  2 // SOMETHING WAS ALREADY THERE

// Defines for move processing
#define MOVE_OK         1
#define MOVE_COLLISION  2
#define MOVE_OOB        3

// Defines for game states
#define IN_PROGRESS     1
#define X_WINS          2
#define O_WINS          3
#define TIE             4
#define ERROR           5

// Define win condition 
#define WIN_REQUIREMENT 3

// Define victory codes
#define VICTORY_NONE    0
#define VICTORY_MARKONE 1
#define VICTORY_MARKTWO 2
#define VICTORY_TIE     3

// Function prototypes
void InitializeBoard(char[ROWS][COLS]);
void DisplayBoard(char[ROWS][COLS]);
int  PlayerMove(int, int, char[ROWS][COLS], char);
int  VictoryCheck(char[ROWS][COLS]);
void DisplayGameResult(int, char, char);

// Main function
int main() {
    // ASCII art and game setup
    printf("|*|*|*|*|*|*|*|*|*|*|*|*|*|*|*|*|*|*|*|*|*|*|*|*|*|*|*|*|*|\n");
    printf(" _____  _         _____                _____                \n");
    printf("|_   _|(_)       |_   _|              |_   _|                \n");
    printf("  | |   _   ___    | |    __ _   ___    | |    ___    ___    \n");
    printf("  | |  | | / __|   | |   / _` | / __|   | |   / _ \\  / _ \\  \n");
    printf("  | |  | || (__    | |  | (_| || (__    | |  | (_) ||  __/  \ \n");
    printf("  \\_/  |_| \\___|   \\_/   \\__,_| \\___|   \\_/   \\___/  \\___|\n");
    printf("                                                               \n");
    printf("|*|*|*|*|*|*|*|*|*|*|*|*|*|*|*|*|*|*|*|*|*|*|*|*|*|*|*|*|*|\n\n");

    // Player names input
    char nameOne[20], nameTwo[20];
    printf("Player 1, please input your name: ");
    scanf("%s", nameOne);
    rewind(stdin);
    printf("Player 2, please input your name: ");
    scanf("%s", nameTwo);
    rewind(stdin);

    // Initialize the game board
    char board[ROWS][COLS];
    InitializeBoard(board);
    int result = 0;
    int gameLoop = 1;

    // Player moves
    printf("\n%s, you are player %c\n", nameOne, MARKONE);
    printf("%s, you are player %c\n\n", nameTwo, MARKTWO);

    // Game loop -- will prompt for input, clear phantom, check result and move to next player if no end condition.

    // Player one
    while (gameLoop) {
        DisplayBoard(board);
        int row, col;
        printf("%s's turn. Enter row and column (e.g., 1 2): ", nameOne);
        scanf("%d %d", &row, &col);
        rewind(stdin);
        result = PlayerMove(row, col, board, MARKONE);
        if (result == MOVE_OK) {
            result = VictoryCheck(board);
            if (result != VICTORY_NONE) {
                DisplayBoard(board);
                DisplayGameResult(result, MARKONE, MARKTWO);
                break;
            }
        }

        // Player two 
        DisplayBoard(board);
        printf("%s's turn. Enter row and column (e.g., 1 2): ", nameTwo);
        scanf("%d %d", &row, &col);
        rewind(stdin);
        result = PlayerMove(row, col, board, MARKTWO);
        if (result == MOVE_OK) {
            result = VictoryCheck(board);
            if (result != VICTORY_NONE) {
                DisplayBoard(board);
                DisplayGameResult(result, MARKONE, MARKTWO);
                break;
            }
        }
    }

    // Wait for user input before exiting
    printf("Press any key to exit.");
    _getch();
    return 0;
}

// Functions

// Initialize board by setting the cells to blank
void InitializeBoard(char board[ROWS][COLS]) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            board[i][j] = BLANK;
        }
    }
}

// Print column, row  and display the board
void DisplayBoard(char board[ROWS][COLS]) {
    printf("   ");
    for (int j = 0; j < COLS; j++) {
        printf("%3d", j + 1);
    }
    printf("\n");

    for (int i = 0; i < ROWS; i++) {
        printf("%3d|", i + 1);
        for (int j = 0; j < COLS; j++) {
            printf("%2c|", board[i][j]);
        }

        printf("\n   ");
        for (int j = 0; j < COLS; j++) {
            printf("+--");
        }
        printf("\n");
    }
}

// Player move function
int PlayerMove(int requestedRow, int requestedColumn, char theBoard[ROWS][COLS], char symbol) {

    // Check if the move is out of bounds
    if (requestedRow > ROWS || requestedColumn > COLS ||
        requestedRow <= 0 || requestedColumn <= 0) {
        printf("ERROR: Move out of bounds!\n");
        return MOVE_OOB;
    }
    // Check if the move causes a collision
    else if (theBoard[requestedRow - 1][requestedColumn - 1] != BLANK) {
        printf("ERROR: Cannot move there, space taken!\n");
        return MOVE_COLLISION;
    }
    else {
        theBoard[requestedRow - 1][requestedColumn - 1] = symbol;
        //printf("Move success!\n"); commented out for clarity
        return MOVE_OK;
    }
}

// Print game results
void DisplayGameResult(int result, char symbol1, char symbol2) {
    switch (result) {
    case VICTORY_MARKONE:
        printf(" Player %c wins!\n", symbol1);
        printf("\n ****************************TIC TAC TOE****************************\n");
        break;
    case VICTORY_MARKTWO:
        printf(" Player %c wins!\n", symbol2);
        printf("\n ****************************TIC TAC TOE****************************\n");
        break;
    case VICTORY_TIE:
        printf(" It's a tie!\n");
        printf("\n ****************************TIC TAC TOE****************************\n");
        break;
    default:
        printf(" Error in game state. Cannot have two winners.\n");
        printf("\n ****************************TIC TAC TOE****************************\n");
        break;
    }
    printf("\n");
}

// Victory check function
int VictoryCheck(char checkMe[ROWS][COLS]) {
    int blankSeen = FALSE;
    int XPresents = FALSE;
    int OPresents = FALSE;

    // Check for any blank space on the board
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (checkMe[i][j] == BLANK)
                blankSeen = TRUE;
        }
    }

    // Check for victory conditions
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            char symbol = checkMe[i][j];

            // Check vertically
            if (i <= ROWS - WIN_REQUIREMENT) {
                int count = 0;
                for (int k = 0; k < WIN_REQUIREMENT; k++) {
                    if (checkMe[i + k][j] == symbol && symbol != BLANK)
                        count++;
                }
                if (count == WIN_REQUIREMENT)
                    (symbol == MARKONE) ? (XPresents = TRUE) : (OPresents = TRUE);
            }

            // Check horizontally
            if (j <= COLS - WIN_REQUIREMENT) {
                int count = 0;
                for (int k = 0; k < WIN_REQUIREMENT; k++) {
                    if (checkMe[i][j + k] == symbol && symbol != BLANK)
                        count++;
                }
                if (count == WIN_REQUIREMENT)
                    (symbol == MARKONE) ? (XPresents = TRUE) : (OPresents = TRUE);
            }

            // Check diagonally (down-right)
            if (i <= ROWS - WIN_REQUIREMENT && j <= COLS - WIN_REQUIREMENT) {
                int count = 0;
                for (int k = 0; k < WIN_REQUIREMENT; k++) {
                    if (checkMe[i + k][j + k] == symbol && symbol != BLANK)
                        count++;
                }
                if (count == WIN_REQUIREMENT)
                    (symbol == MARKONE) ? (XPresents = TRUE) : (OPresents = TRUE);
            }

            // Check diagonally (up-right)
            if (i >= WIN_REQUIREMENT - 1 && j <= COLS - WIN_REQUIREMENT) {
                int count = 0;
                for (int k = 0; k < WIN_REQUIREMENT; k++) {
                    if (checkMe[i - k][j + k] == symbol && symbol != BLANK)
                        count++;
                }
                if (count == WIN_REQUIREMENT)
                    (symbol == MARKONE) ? (XPresents = TRUE) : (OPresents = TRUE);
            }
        }
    }

    // Determine the result based on X and O presenting victory
    if (XPresents && OPresents)
        return ERROR; // Both X and O present victory - an error condition
    else if (XPresents)
        return VICTORY_MARKONE; // X presents victory
    else if (OPresents)
        return VICTORY_MARKTWO; // O presents victory
    else if (blankSeen)
        return VICTORY_NONE; // Game still in progress
    else
        return VICTORY_TIE; // Tie condition
}
