#include<iostream>
#include<cstdlib>

#include"piece.h"

using namespace std;

//************************************************************************

// Piece Class Member Functions

//************************************************************************

char Piece::get_colour() const{
    return colour;
}

char Piece::get_piece_type() const{
    return piece_type;
};


bool Piece::legal_right(int row, int start_col, int dest_col, Piece* board[8][8]){

    // cout << endl <<  "hi" << endl;

    for (int col = (start_col + 1); col < dest_col; col++){

        if (board[row][col] != nullptr){
            // cout << "row " << row << " column " << col << " has a piece in it!" << endl;
            return false;
        }
        // cout << "row " << row << " column " << col << " doesn't have a piece in it!" << endl;
    }
    return true;
}

bool Piece::legal_left(int row, int start_col, int dest_col, Piece* board[8][8]){

    for (int col = (start_col - 1); col > dest_col; col--){

        if (board[row][col] != nullptr){
                return false;
        }
    }
    return true;
}

bool Piece::legal_up(int start_row, int dest_row, int col, Piece* board[8][8]){
    for (int row = (start_row - 1); row > dest_row; row--){

            if (board[row][col] != nullptr){
                return false;
            }
    }
    return true;
}

bool Piece::legal_down(int start_row, int dest_row, int col, Piece* board[8][8]){
    for (int row = (start_row + 1); row < dest_row; row++){
        
            if (board[row][col] != nullptr){
                // cout << "row " << row << " column " << col << " has a piece in it!" << endl;
                return false;
            }
        // cout << "row " << row << " column " << col << " doesn't have a piece in it!" << endl;
        }
    return true;
}

bool Piece::legal_right_up_diagonal(int start_row, int start_col, int steps, Piece* board[8][8]){
    // int steps = abs(dest_row-start_row);
    // cout << endl << "steps: " << steps << endl;

    for (int n = 1; n < steps; n++){
        // cout << "value of n: " << n << endl;
        if (board[ (start_row-n) ][ (start_col+n) ] != nullptr){
            // cout << "row " << (start_row-n) << " column " << (start_col+n) << " has a piece in it!" << endl;
            return false;
        }
        // cout << "row " << (start_row-n) << " column " << (start_col+n) << " doesn't have a piece in it!" << endl;
    }
    return true;
}

bool Piece::legal_left_up_diagonal(int start_row, int start_col, int steps, Piece* board[8][8]){
    // cout << endl << "steps: " << steps << endl;

    for (int n = 1; n < steps; n++){
        // cout << "value of n: " << n << endl;
        if (board[ (start_row-n) ][ (start_col-n) ] != nullptr){
            // cout << "row " << (start_row-n) << " column " << (start_col+n) << " has a piece in it!" << endl;
            return false;
        }
        // cout << "row " << (start_row-n) << " column " << (start_col+n) << " doesn't have a piece in it!" << endl;
    }
    return true;
}

bool Piece::legal_right_down_diagonal(int start_row, int start_col, int steps, Piece* board[8][8]){
   // cout << endl << "steps: " << steps << endl;

    for (int n = 1; n < steps; n++){
        // cout << "value of n: " << n << endl;
        if (board[ (start_row+n) ][ (start_col+n) ] != nullptr){
            // cout << "row " << (start_row-n) << " column " << (start_col+n) << " has a piece in it!" << endl;
            return false;
        }
        // cout << "row " << (start_row-n) << " column " << (start_col+n) << " doesn't have a piece in it!" << endl;
    }
    return true;
}

bool Piece::legal_left_down_diagonal(int start_row, int start_col, int steps, Piece* board[8][8]){
    // cout << endl << "steps: " << steps << endl;

    for (int n = 1; n < steps; n++){
        // cout << "value of n: " << n << endl;
        if (board[ (start_row+n) ][ (start_col-n) ] != nullptr){
            // cout << "row " << (start_row-n) << " column " << (start_col+n) << " has a piece in it!" << endl;
            return false;
        }
        // cout << "row " << (start_row-n) << " column " << (start_col+n) << " doesn't have a piece in it!" << endl;
    }
    return true;
}