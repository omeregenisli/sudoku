#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#define ismail 30
#define SIZE 9

// score, board
int board[SIZE][SIZE];
int score = 0;

// pieces
int pieces[10][4][4] = {
    {{1}},                    // 1X1
    {{1, 1}},                 // horiz 2
    {{1}, {1}},               // vert 2
    {{1, 1, 1}},              // horiz 3
    {{1}, {1}, {1}},          // vert 3
    {{1, 1}, {1, 0}},         // L1
    {{1, 1}, {0, 1}},         // L2
    {{1, 1}, {1, 1}},         // 2x2
    {{1,0},{1,1}},            // L3
    {{0,1},{1,1}}             // L4
};
int piece_widths[10] = { 1, 2, 1, 3, 1, 2, 2, 2, 2, 2 };
int piece_heights[10] = { 1, 1, 2, 1, 3, 2, 2, 2, 2, 2 };

void initialize_random_board(void) {
    int filled_cells = 0;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (filled_cells < ismail) {
                if (rand() % 2 == 0) {
                    board[i][j] = rand() % 2;
                    filled_cells++;
                }
                else {
                    board[i][j] = -1;
                }
            }
            else {
                board[i][j] = -1;
            }
        }
    }
}

// printboard
void printBoard(void) {
    printf("    A   B   C   D   E   F   G   H   I");
    printf("\n  + - - - - - + - - - - - + - - - - - +");
    for (int i = 0; i < SIZE; i++) {
        printf("\n%d |", i + 1);
        for (int j = 0; j < SIZE; j++) {
            if (j == 2 || j == 5 || j == 8) {
                if (board[i][j] == -1) {
                    printf(" . |");
                }
                else {
                    printf(" %d |", board[i][j]);
                }
            }
            else {
                if (board[i][j] == -1) {
                    printf(" .  ");
                }
                else {
                    printf(" %d  ", board[i][j]);
                }
            }
        }
        if (i == 0 || i == 1 || i == 3 || i == 4 || i == 6 || i == 7) {
            printf("\n  |           |           |           |");
        }
        if ((i + 1) % 3 == 0) {
            printf("\n  + - - - - - + - - - - - + - - - - - +");
        }
    }printf("\nScore: %d\n", score);
}

// randpiece
void generate_piece(int piece[4][4], int* width, int* height) {
    int num = rand() % 10;
    *width = piece_widths[num];
    *height = piece_heights[num];

    for (int i = 0; i < *height; i++) {
        for (int j = 0; j < *width; j++) {
            piece[i][j] = pieces[num][i][j];
        }
    }
}

// placepiecefunc
int place_piece(int piece[4][4], int width, int height, int row, int col) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (piece[i][j] != 0) { // check 1010
                if (row + i >= SIZE || col + j >= SIZE || board[row + i][col + j] != -1) {
                    return 0; // cant_place
                }
            }
        }
    }

    //placepiece
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (piece[i][j] != 0 || piece[i][j] == 0) { //write 1010
                board[row + i][col + j] = piece[i][j];
            }
        }
    }
    return 1; // success
}

// CHECKING_EMPTY_OR_NOT
int valid_invalid(int piece[4][4], int width, int height, int row, int col) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (piece[i][j] != 0) {
                if (row + i >= SIZE || col + j >= SIZE || board[row + i][col + j] != -1) {
                    return 0; // unplacable
                }
            }
        }
    }
    return 1; // PLACABLE
}


void check_clear() {
    int multiplier = 0;
    int tempScore = 0;

    // ROW check (binary calculation from right to left)
    for (int i = 0; i < SIZE; i++) {
        int full = 1;
        int binaryValue = 0;
        for (int j = SIZE - 1; j >= 0; j--) {
            if (board[i][j] == -1) {
                full = 0;
                break;
            }
            binaryValue += board[i][j] * (1 << (SIZE - 1 - j)); // build the binary number from right to left
        }
        if (full) { // Row is full
            tempScore += binaryValue; // Add the binary value as score
            multiplier++;
            for (int j = 0; j < SIZE; j++) {
                board[i][j] = -1;
            }
        }
    }

    // COL check (binary calculation from top to bottom)
    for (int j = 0; j < SIZE; j++) {
        int full = 1;
        int binaryValue = 0;
        for (int i = 0; i < SIZE; i++) {
            if (board[i][j] == -1) {
                full = 0;
                break;
            }
            binaryValue |= (1 << (SIZE - 1 - i)); // build the binary number from top to bottom
        }
        if (full) { // Column is full
            tempScore += binaryValue; // Add the binary value as score
            multiplier++;
            for (int i = 0; i < SIZE; i++) {
                board[i][j] = -1;
            }
        }
    }

    // 3x3 blocks check (binary calculation from right to left, row by row)
    for (int blockRow = 0; blockRow < 3; blockRow++) {
        for (int blockCol = 0; blockCol < 3; blockCol++) {
            int full = 1;
            int binaryValue = 0;
            for (int i = blockRow * 3; i < (blockRow + 1) * 3; i++) {
                for (int j = blockCol * 3; j < (blockCol + 1) * 3; j++) {
                    if (board[i][j] == -1) {
                        full = 0;
                        break;
                    }
                    binaryValue += board[i][j] * (1 << (SIZE - 1 - j)); // build the binary number from right to left for each row in the block
                }
                if (!full) break;
            }
            if (full) { // Block is full
                tempScore += binaryValue; // Add the binary value as score
                multiplier++;
                for (int i = blockRow * 3; i < (blockRow + 1) * 3; i++) {
                    for (int j = blockCol * 3; j < (blockCol + 1) * 3; j++) {
                        board[i][j] = -1;
                    }
                }
            }
        }
    }

    // Final score adjustment
    score += tempScore * multiplier;
}

// CheckEmpty
int game_over(int piece[4][4], int width, int height) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (valid_invalid(piece, width, height, i, j)) {
                return 0;
            }
        }
    }
    return 1; //no placement
}

// GAME
int main() {
    srand(time(NULL));
    // Tahtayý -1 ile dolduruyoruz
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            board[i][j] = -1;
        }
    }

    printf("Welcome to Binary Sudoku!\n");
    initialize_random_board();

    while (1) {
        printBoard();
        int current_piece[4][4];
        int width, height;
        generate_piece(current_piece, &width, &height);

        printf("\nNew Piece:\n");
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                printf("%d ", current_piece[i][j]);
            }
            printf("\n");
        }

        //get input
        char col_char;
        int row, col;
        printf("Enter location (ex  A1): ");
        scanf(" %c%d", &col_char, &row);
        col = col_char - 'A';
        row--;

        if (!place_piece(current_piece, width, height, row, col)) {
            printf("Invalid move, try again.\n");
            continue;
        }
        check_clear();
        if (game_over(current_piece, width, height)) {
            printf("Game over! Final Score: %d\n", score);
            break;
        }
    }
    return 0;
}