#ifndef KING_H
#define KING_H

#include"piece.h"

//************************************************************************
// King Class Header File
//************************************************************************


class King : public Piece{

public:

    bool possible_move(int start_col, int start_row, int dest_col, int dest_row) override;
    bool legal_move(int start_row, int start_col, int dest_row, int dest_col, Piece* board[8][8]) override;

    // Constructor (N) Array initialiser list
    King (char colour, char piece_type)
      : Piece(colour, piece_type){};

};

#endif