#include<iostream>
#include<cstdlib>

#include"king.h"

using namespace std;

//************************************************************************

// King Class Member Functions

//************************************************************************

bool King::possible_move(int start_col, int start_row, int dest_col, int dest_row){

    // Moving 1 space horizontally
    if ( start_col == dest_col && abs(start_row - dest_row) == 1){
        return true;
    }

    // Moving 1 space vertically
    if ( start_row == dest_row && abs(start_col - dest_col) == 1){
        return true;
    }

    // Moving 1 space up diagonally right
    if ( dest_row == (start_row-1) && dest_col == (start_col+1) ){
        return true;
    }

    // Moving 1 space up diagonally left
    if ( dest_row == (start_row-1) && dest_col == (start_col-1) ){
        return true;
    }

    // Moving 1 space down diagonally right
    if ( dest_row == (start_row+1) && dest_col == (start_col+1) ){
        return true;
    }

    // Moving 1 space down diagonally left
    if ( dest_row == (start_row+1) && dest_col == (start_col-1) ){
        return true;
    }

    // No other possible moves
    return false;

}

bool King::legal_move(int start_row, int start_col, int dest_row, int dest_col, Piece* board[8][8]){

     // Not taking own piece
    if ( board[dest_row][dest_col] != nullptr &&
         board[start_row][start_col]->colour == board[dest_row][dest_col]->colour ){
        return false;
    }

    // Can jump pieces
    if ( possible_move(start_col, start_row, dest_col, dest_row) ){
        return true;
    }
    else{
        return false;
    }

}