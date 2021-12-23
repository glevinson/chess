#include<iostream>
#include<cstdlib>

#include"queen.h"

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

bool Queen::legal_move(int start_row, int start_col, int dest_row, int dest_col, Piece* board[8][8]){
    
    int steps = abs(dest_row-start_row);

    // Not taking own piece
    if ( board[dest_row][dest_col] != nullptr &&
         board[start_row][start_col]->get_colour() == board[dest_row][dest_col]->get_colour() ){
        return false;
    }

    // Checking no pieces in path:

    //  When moving right
    if ( start_row == dest_row && dest_col > start_col) {
        return legal_right(dest_row, start_col, dest_col, board);
    }

    // When moving left
    if ( start_row == dest_row && dest_col < start_col) {
        return legal_left(start_col, dest_col, dest_row, board);
    }

    // When moving up
    if ( start_col == dest_col && dest_row < start_row) {
        return legal_up(start_row, dest_row, dest_col, board);
    }

    // When moving down
    if ( start_col == dest_col && dest_row > start_row) {
        return legal_down(start_row, dest_row, dest_col, board);
    }

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

    return false;
}