/* 
 * File:   reversi.h
 * Author: Amine Yesilyurt
 * Created on 23 September 2015, 11:55
 */

#ifndef REVERSI_H
#define	REVERSI_H

#include <cstdlib>
#include <cctype>
#include<cstdio>
#include<cassert>

#define SIZE 6  /* Board size - must be even */

void display(char board[][SIZE]);
int valid_moves(char board[][SIZE], int moves[][SIZE], char player);
void computer_move(char board[][SIZE], int moves[][SIZE], char player);
int get_score(char board[][SIZE], char player);
int best_move(char board[][SIZE], int moves[][SIZE], char player);
void make_move(char board[][SIZE], int row, int col, char player);
#endif	/* REVERSI_H */

