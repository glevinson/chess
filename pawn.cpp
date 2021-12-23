#include<iostream>
#include<cstdlib>

#include"pawn.h"

using namespace std;

bool Pawn::possible_move(int start_col, int start_row, int dest_col, int dest_row){

    // Moving forward:

    // Black forward 1 space
    if ( colour == 'B' && start_col == dest_col && dest_row == (start_row+1) ){
        return true;
    }

    // White forward 1 space
    if ( colour == 'W' && start_col == dest_col && dest_row == (start_row-1) ){
        return true;
    }

    // Black forward 2 spaces
    if ( colour == 'B' && start_row == 1 && start_col == dest_col && dest_row == (start_row+2) ){
        return true;
    }

    // White forward 2 spaces
    if ( colour == 'W' && start_row == 6 && start_col == dest_col && dest_row == (start_row-2) ){
        return true;
    }

    // Moving diagonally :

    // Black down diagonally right 1 space
    if (colour == 'B' && dest_row == (start_row+1) && dest_col == (start_col+1) ){
        return true;
    }

    // Black down diagonally left 1 space
    if (colour == 'B' && dest_row == (start_row+1) && dest_col == (start_col-1) ){
        return true;
    }

    // White up diagonally right 1 space
    if (colour == 'W' && dest_row == (start_row-1) && dest_col == (start_col+1) ){
        return true;
    }

    // White up diagonally left 1 space
    if (colour == 'W' && dest_row == (start_row-1) && dest_col == (start_col-1) ){
        return true;
    }

    // No other possible moves
    return false;

}

bool Pawn::legal_move(int start_row, int start_col, int dest_row, int dest_col, Piece* board[8][8]){

    // Cannot move diagonally if square is empty
    if ( start_col != dest_col && board[dest_row][dest_col] == nullptr){
        return false;
    }

    // Cannot move diagonally unless taking opposition piece
    if ( start_col != dest_col && 
         board[dest_row][dest_col]->get_colour() == board[start_row][start_col]->get_colour()){
        return false;
    }

    // Cannot move forward into any piece
    if ( start_col == dest_col && board[dest_row][dest_col] != nullptr ){
        return false;
    }

    // Cannot move 2 spaces if another piece in path
    if ( start_col == dest_col && dest_row == (start_row + 2) && board[start_row+1][dest_col] != nullptr){
        return false;
    }

    return true;
}