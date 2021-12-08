#ifndef CHESSBOARD_H
#define CHESSBOARD_H

// #include"piece.h"
// #include"pawn.h"
// #include"castle.h"
// #include"bishop.h"
// #include"knight.h"
// #include"king.h"
// #include"queen.h"


//************************************************************************

// Piece Class

//************************************************************************

class Piece{

  public:

    // Data Mambers:

    char colour;
    char piece_type;

    // Member Functions:

    char get_colour();
    char get_piece_type();
    virtual bool possible_move(int start_col, int start_row, int dest_col, int dest_row) = 0;
    virtual bool legal_move(int start_col, int start_row, int dest_col, int dest_row, Piece* board[8][8]) = 0;

    bool legal_right(int start_col, int dest_col, int dest_row, Piece* board[8][8]);

    // Constructor
    Piece (char colour, char piece_type)
      : colour(colour),
          piece_type(piece_type){};
};

//************************************************************************

// Pawn Class

//************************************************************************


class Pawn : public Piece{

  public:

    bool possible_move(int start_col, int start_row, int dest_col, int dest_row) override {return true;};
    bool legal_move(int start_col, int start_row, int dest_col, int dest_row, Piece* board[8][8]) override {return true;};

    // Constructor
    Pawn (char colour, char piece_type)
      : Piece(colour, piece_type){};
};

//************************************************************************

// Castle Class

//************************************************************************

class Castle : public Piece{

  public:

    bool possible_move(int start_col, int start_row, int dest_col, int dest_row) override;
    bool legal_move(int start_col, int start_row, int dest_col, int dest_row, Piece* board[8][8]) override;

    // Constructor
    Castle (char colour, char piece_type)
      : Piece(colour, piece_type){};

};

//************************************************************************

// Knight Class

//************************************************************************

class Knight : public Piece{

  public:
 
    bool possible_move(int start_col, int start_row, int dest_col, int dest_row) override;
    bool legal_move(int start_col, int start_row, int dest_col, int dest_row, Piece* board[8][8]) override {return true;};

    // Constructor
    Knight (char colour, char piece_type)
      : Piece(colour, piece_type){};

};


//************************************************************************

// Bishop Class

//************************************************************************


class Bishop : public Piece{

  public:

    bool possible_move(int start_col, int start_row, int dest_col, int dest_row) override;
    bool legal_move(int start_col, int start_row, int dest_col, int dest_row, Piece* board[8][8]) override {return true;};

      // Constructor
      Bishop (char colour, char piece_type)
        : Piece(colour, piece_type){};

};

//************************************************************************

// Queen Class

//************************************************************************

class Queen : public Piece{

public:
 
    bool possible_move(int start_col, int start_row, int dest_col, int dest_row) override;
    bool legal_move(int start_col, int start_row, int dest_col, int dest_row, Piece* board[8][8]) override {return true;};

    // Constructor
    Queen (char colour, char piece_type)
      : Piece(colour, piece_type){};

};


//************************************************************************

// King Class

//************************************************************************


class King : public Piece{

public:

    int position[2];
    bool possible_move(int start_col, int start_row, int dest_col, int dest_row) override;
    bool legal_move(int start_col, int start_row, int dest_col, int dest_row, Piece* board[8][8]) override {return true;};

    // Constructor (N) Array initialiser list
    King (char colour, char piece_type, int starting_row, int starting_column)
      : Piece(colour, piece_type),
          position{starting_row, starting_column}{};

};

// ************************************************************************

// ChessBoard Class (Bottom white, Top black)

// ************************************************************************

class ChessBoard{

public:

    // Data Members:

    Piece* board[8][8];

    // Member Functions

    void print_board();
    void submitMove(char source_square[], char distination_square[]);
    void convert_to_index(char source_square[3], char destination_square[3],
                          int source[2], int destination[2]);
    void load_board(Piece* board[8][8]);

    // Constructor
    ChessBoard(){ load_board(board); };

};

#endif
