#ifndef PIECE_H
#define PIECE_H

//************************************************************************
// Piece Class
//************************************************************************

class Piece{

  private:

    // Data Mambers:

    char colour;
    char piece_type;

    // Member Functions:
    virtual bool possible_move(int start_col, int start_row, int dest_col, int dest_row) = 0;
    virtual bool legal_move(int start_row, int start_col, int dest_row, int dest_col, Piece* board[8][8]) = 0;

    // WORKS
    bool legal_right(int row, int start_col, int dest_col, Piece* board[8][8]);
    // WORKS
    bool legal_left(int row, int start_col, int dest_col, Piece* board[8][8]);
    bool legal_up(int start_row, int dest_row, int col, Piece* board[8][8]);
    bool legal_down(int start_row, int dest_row, int col, Piece* board[8][8]);

    // will need to include: int steps = abs(dest_row-start_row);
    bool legal_right_up_diagonal(int start_row, int start_col, int steps, Piece* board[8][8]);
    bool legal_left_up_diagonal(int start_row, int start_col, int steps, Piece* board[8][8]);
    bool legal_left_down_diagonal(int start_row, int start_col, int steps, Piece* board[8][8]);
    bool legal_right_down_diagonal(int start_row, int start_col, int steps, Piece* board[8][8]);

  public:
  
    char get_colour() const;
    char get_piece_type() const;

    // Constructor
    Piece (char colour, char piece_type)
      : colour(colour),
          piece_type(piece_type){};
};

#endif