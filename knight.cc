#include<iostream>
#include<cstdlib>

#include"knight.h"
#include"piece.h"
#include"ChessBoard.h"

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