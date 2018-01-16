/* 
 * File:   main.cpp
 * Author: Amine Yesilyurt
 *
 * Created on 23 September 2015, 11:51
 */


#include<iostream>
#include "reversi.cpp"
#include "reversi.h"
using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {

    {
        char board [SIZE][SIZE] = {0}; /* The board           */
        int moves[SIZE][SIZE] = {0}; /* Valid moves         */
        int row = 0; /* Board row index     */
        int col = 0; /* Board column index  */
        int no_of_games = 0; /* Number of games     */
        int no_of_moves = 0; /* Count of moves      */
        int invalid_moves = 0; /* Invalid move count  */
        int comp_score = 0; /* Computer score      */
        int user_score = 0; /* Player score        */
        char y = 0; /* Column letter       */
        int x = 0; /* Row number          */
        char again = 0; /* Replay choice input */
        int player = 0; /* Player indicator    */

        printf("\nREVERSI\n\n");
        printf("You can go first on the first game, then we will take turns.\n");
        printf("   You will be white - (O)\n   I will be black   - (@).\n");
        printf("Select a square for your move by typing a digit for the row\n "
                "and a letter for the column with no spaces between.\n");
        printf("\nGood luck!  Press Enter to start.\n");
        scanf("%c", &again);

        /* Prompt for how to play - as before */

        /* The main game loop */
        do {
            /* On even games the player starts; */
            /* on odd games the computer starts */
            player = ++no_of_games % 2;
            no_of_moves = 4; /* Starts with four counters */

            /* Blank all the board squares */
            for (row = 0; row < SIZE; row++)
                for (col = 0; col < SIZE; col++)
                    board[row][col] = ' ';

            /* Place the initial four counters in the center */
            board[SIZE / 2 - 1][SIZE / 2 - 1] = board[SIZE / 2][SIZE / 2] = 'O';
            board[SIZE / 2 - 1][SIZE / 2] = board[SIZE / 2][SIZE / 2 - 1] = '@';

            /* The game play loop */
            do {
                display(board); /* Display the board  */
                if (player++ % 2) { /*   It is the player's turn                    */
                    if (valid_moves(board, moves, 'O')) {
                        /* Read player moves until a valid move is entered */
                        for (;;) {
                            fflush(stdin); /* Flush the keyboard buffer */
                            printf("Please enter your move (row column): ");
                            scanf("%d%c", &x, &y); /* Read input        */
                            y = tolower(y) - 'a'; /* Convert to column index */
                            x--; /* Convert to row index    */
                            if (x >= 0 && y >= 0 && x < SIZE && y < SIZE && moves[x][y]) {
                                make_move(board, x, y, 'O');
                                no_of_moves++; /* Increment move count */
                                break;
                            } else
                                printf("Not a valid move, try again.\n");
                        }
                    } else /* No valid moves */
                        if (++invalid_moves < 2) {
                        fflush(stdin);
                        printf("\nYou have to pass, press return");
                        scanf("%c", &again);
                    } else
                        printf("\nNeither of us can go, so the game is over.\n");
                } else { /* It is the computer's turn                    */
                    if (valid_moves(board, moves, '@')) /* Check for valid moves */ {
                        invalid_moves = 0; /* Reset invalid count   */
                        computer_move(board, moves, '@');
                        no_of_moves++; /* Increment move count  */
                    } else {
                        if (++invalid_moves < 2)
                            printf("\nI have to pass, your go\n"); /* No valid move */
                        else
                            printf("\nNeither of us can go, so the game is over.\n");
                    }
                }
            } while (no_of_moves < SIZE * SIZE && invalid_moves < 2);

            /* Game is over */
            display(board); /* Show final board */

            /* Get final scores and display them */
            comp_score = user_score = 0;
            for (row = 0; row < SIZE; row++)
                for (col = 0; col < SIZE; col++) {
                    comp_score += board[row][col] == '@';
                    user_score += board[row][col] == 'O';
                }
            printf("The final score is:\n");
            printf("Computer %d\n    User %d\n\n", comp_score, user_score);

            fflush(stdin); /* Flush the input buffer */
            printf("Do you want to play again (y/n): ");
            scanf("%c", &again); /* Get y or n             */
        } while (tolower(again) == 'y'); /* Go again on y          */

        printf("\nGoodbye\n");
    }

    return 0;
}

