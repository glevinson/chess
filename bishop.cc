#include<iostream>
#include<cstdlib>

#include"piece.h"
#include"bishop.h"
#include"ChessBoard.h

using namespace std;

//************************************************************************

// Bishop Class Member Functions

//************************************************************************

bool Bishop::possible_move(int start_col, int start_row, int dest_col, int dest_row){

    // if move diagonally, the difference between start row & destination row should
    // equal the difference between start column & destination column
    if ( abs(start_row - dest_row) == abs(start_col - dest_col) ){
        return true;
    }

    // No other possible moves
    return false;
}