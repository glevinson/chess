#include<iostream>
#include<cstdlib>

#include"piece.h"

using namespace std;

//************************************************************************

// Piece Class Member Functions

//************************************************************************

char Piece::get_colour(){
    return colour;
}

char Piece::get_piece_type(){
    return piece_type;
};

bool Piece::legal_right(int start_col, int dest_col, int dest_row, Piece* board[8][8]){

    for (int col = (start_col + 1); col < dest_col; col++){

        if (cb->board[dest_row][col] != NULL){
                return false;
        }
    }
}