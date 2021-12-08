#include<iostream>
#include<cstdlib>

#include"piece.h"
#include"queen.h"
#include"ChessBoard.h

using namespace std;

//************************************************************************

// Queen Class Member Functions

//************************************************************************

bool Queen::possible_move(int start_col, int start_row, int dest_col, int dest_row){

    // Moving diagonally
    if ( abs(start_row - dest_row) == abs(start_col - dest_col) ){
        return true;
    }

    // Moving horizontally
    if ( start_row == dest_row && start_col != dest_col ){
        return true;
    }

    // Moving vertically
    if ( start_col == dest_col && start_row != dest_row ){
        return true;
    }

    // No other possible moves
    return false;
}