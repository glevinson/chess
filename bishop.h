#ifndef BISHOP_H
#define BISHOP_H

#include"piece.h"

//************************************************************************
// Bishop Class Header File
//************************************************************************


class Bishop : public Piece{

  public:

    bool possible_move(int start_col, int start_row, int dest_col, int dest_row) override;
    bool legal_move(int start_row, int start_col, int dest_row, int dest_col, Piece* board[8][8]) override;

      // Constructor
      Bishop (char colour, char piece_type)
        : Piece(colour, piece_type){};

};

#endif