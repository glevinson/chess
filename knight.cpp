#include<iostream>
#include<cstdlib>

#include"knight.h"

using namespace std;

//************************************************************************

// Knight Class Member Functions

//************************************************************************

bool Knight::possible_move(int start_col, int start_row, int dest_col, int dest_row){

    // Moving 2 spaces horizontally & 1 space vertically
    if (dest_row == start_row - 2 || dest_row == start_row + 2){
        if (dest_col == start_col - 1 || dest_col == start_col + 1){
            return true;
        }
    }
    
    // Moving 2 spaces vertically & 1 space horiztonally
    if (dest_col == start_col - 2 || dest_col == start_col + 2){
        if (dest_row == start_row - 1 || dest_row == start_row + 1){
            return true;
        }
    }

    // No other possible moves
    return false;
}

bool Knight::legal_move(int start_row, int start_col, int dest_row, int dest_col, Piece* board[8][8]){

    // Testing not taking own piece
    if ( board[dest_row][dest_col] != nullptr &&
         board[start_row][start_col]->get_colour() == board[dest_row][dest_col]->get_colour() ){
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