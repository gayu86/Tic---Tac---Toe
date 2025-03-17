#include <stdio.h>
#include <stdlib.h>
#include <time.h>

char board[3][3];

void initializeBoard() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            board[i][j] = '1' + (i * 3 + j);
        }
    }
}

void printBoard() {
    printf("\n");
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf(" %c ", board[i][j]);
            if (j < 2) printf("|");
        }
        printf("\n");
        if (i < 2) printf("-----------\n");
    }
    printf("\n");
}

int checkWin() {
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2]) return 1;
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i]) return 1;
    }
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2]) return 1;
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0]) return 1;
    return 0;
}

int isDraw() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] >= '1' && board[i][j] <= '9') return 0;
        }
    }
    return 1;
}

void playGame(int mode) {
    int player = 1, choice;
    char mark;
    initializeBoard();
    srand(time(NULL));

    while (1) {
        printBoard();
        mark = (player == 1) ? 'X' : 'O';

        if (mode == 1 && player == 2) {
            // Computer move (random selection of available spot)
            do {
                choice = (rand() % 9) + 1;
            } while (board[(choice - 1) / 3][(choice - 1) % 3] == 'X' || board[(choice - 1) / 3][(choice - 1) % 3] == 'O');
            printf("Computer chooses: %d\n", choice);
        } else {
            printf("Player %d, enter your choice: ", player);
            scanf("%d", &choice);
        }

        if (choice < 1 || choice > 9) {
            printf("Invalid move! Try again.\n");
            continue;
        }
        
        int row = (choice - 1) / 3;
        int col = (choice - 1) % 3;
        
        if (board[row][col] == 'X' || board[row][col] == 'O') {
            printf("Invalid move! Try again.\n");
            continue;
        }
        
        board[row][col] = mark;

        if (checkWin()) {
            printBoard();
            printf("Player %d wins!\n", player);
            break;
        }

        if (isDraw()) {
            printBoard();
            printf("It's a draw!\n");
            break;
        }
        
        player = (player % 2) + 1;
    }
}

int main() {
    int choice;
    printf("Welcome to Tic-Tac-Toe!\n");
    printf("Select mode:\n1. Play against Computer\n2. Two Players\nEnter your choice: ");
    scanf("%d", &choice);
    
    if (choice == 1 || choice == 2) {
        playGame(choice);
    } else {
        printf("Invalid choice! Exiting...\n");
    }
    
    return 0;
}