#include<iostream>
#include<cstdlib>

#include"piece.h"
#include"castle.h"
#include"ChessBoard.h

using namespace std;

//************************************************************************

// Castle Class Member Functions

//************************************************************************

bool Castle::possible_move(int start_col, int start_row, int dest_col, int dest_row){
// Q: dont have the override in the implementation?

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

bool Castle::legal_move(int start_col, int start_row, int dest_col, int dest_row, ChessBoard* cb){

    // Not taking own piece
    if ( cb->board[start_row][start_col]->colour == cb->board[dest_row][dest_col]->colour ){
        return false;
    }

    // Checking no pieces in path:

    // When moving right
    if ( start_row == dest_row && dest_col > start_col) {
        return legal_right(start_col, dest_col, dest_row, cb );
    }

     // When moving left
    if ( start_row == dest_row && dest_col < start_col) {

        for (int col = (start_col - 1); col > dest_col; col--){

            if (cb->board[dest_row][col] != NULL){
                return false;
            }
        }
    }

    // When moving up
    if ( start_col == dest_col && dest_row > start_row) {

        for (int row = (start_row + 1); row < dest_row; row++){

            if (cb->board[row][dest_col] != NULL){
                return false;
            }
        }
    }

     // When moving down
    if ( start_col == dest_col && dest_row < start_row) {

        for (int row = (start_row - 1); row > dest_row; row--){

            if (cb->board[row][dest_col] != NULL){
                return false;
            }
        }
    }

}