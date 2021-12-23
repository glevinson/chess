#include<iostream>
#include<cstdlib>

#include"bishop.h"

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

bool Bishop::legal_move(int start_row, int start_col, int dest_row, int dest_col, Piece* board[8][8]){

    int steps = abs(dest_row-start_row);

    // Not taking own piece
    if ( board[dest_row][dest_col] != nullptr &&
         board[start_row][start_col]->get_colour() == board[dest_row][dest_col]->get_colour() ){
        // cout << endl << "landed on piece with same colour" << endl;
        return false;
    }

    // Checking no pieces in path:

    // Moving up diagonally left
    if (dest_row < start_row && dest_col < start_col){
        return legal_left_up_diagonal(start_row, start_col, steps, board);
    }

    // Moving up diagonally right
    if (dest_row < start_row && dest_col > start_col){
        return legal_right_up_diagonal(start_row, start_col, steps, board);
    }

    // Moving down diagonally left
    if (dest_row > start_row && dest_col < start_col){
        return legal_left_down_diagonal(start_row, start_col, steps, board);
    }

    // Moving down diagonally right
    if (dest_row > start_row && dest_col > start_col){
        return legal_right_down_diagonal(start_row, start_col, steps, board);
    }

    cout << endl << "Problem - not moving in direction should be! " << endl;
    return false;

}