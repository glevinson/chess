#include<iostream>
#include<cstdlib>

#include"castle.h"

using namespace std;

//************************************************************************

// Castle Class Member Functions

//************************************************************************

bool Castle::possible_move(int start_col, int start_row, int dest_col, int dest_row){

    // Moving horizontally
    if ( start_row == dest_row && start_col != dest_col ){
        return true;
    }

    // Moving vertically
    if ( start_col == dest_col && start_row != dest_row ){
        return true;
    }

    // No other moves are possible
    return false;

}

bool Castle::legal_move(int start_row, int start_col, int dest_row, int dest_col, Piece* board[8][8]){

    // Test not taking own piece
    if ( board[dest_row][dest_col] != nullptr &&
         board[start_row][start_col]->get_colour() == board[dest_row][dest_col]->get_colour() ){
        return false;
    }

    // Checking no pieces in path:

    // When moving right
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
    cout << endl << "Problem - not moving vertically or horizontally!" << endl;
    return false;
}
