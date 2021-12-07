#ifndef CHESSBOARD_H
#define CHESSBOARD_H


//************************************************************************

// Piece Class

//************************************************************************

class Piece{

  public:

    // Data Mambers:

    char colour;

    // Member Functions:

    char get_colour();
    virtual bool valid_move(int start_col, int start_row, int dest_col, int dest_row) = 0;

    // Constructor
    Piece (char colour)
      : colour(colour){};
};

//************************************************************************

// Pawn Class

//************************************************************************


class Pawn : public Piece{

  public:

    bool valid_move(int start_col, int start_row, int dest_col, int dest_row) override {return true;};

    // Constructor
    Pawn (char colour)
      : Piece(colour){};
};

//************************************************************************

// Castle Class

//************************************************************************

class Castle : public Piece{

  public:

    bool valid_move(int start_col, int start_row, int dest_col, int dest_row) override;

    // Constructor
    Castle (char colour)
      : Piece(colour){};

};

//************************************************************************

// Knight Class

//************************************************************************

class Knight : public Piece{

  public:
 
    bool valid_move(int start_col, int start_row, int dest_col, int dest_row) override;

    // Constructor
    Knight (char colour)
      : Piece(colour){};

};


//************************************************************************

// Bishop Class

//************************************************************************


class Bishop : public Piece{

  public:

    bool valid_move(int start_col, int start_row, int dest_col, int dest_row) override;
      // Constructor
      Bishop (char colour)
        : Piece(colour){};

};

//************************************************************************

// Queen Class

//************************************************************************

class Queen : public Piece{

public:
 
    bool valid_move(int start_col, int start_row, int dest_col, int dest_row) override{return true;};

    // Constructor
    Queen (char colour)
      : Piece(colour){};

};


//************************************************************************

// King Class

//************************************************************************


class King : public Piece{

public:

    // char position[3];
    bool valid_move(int start_col, int start_row, int dest_col, int dest_row) override{return true;};

    // Constructor
    King (char colour)
      : Piece(colour){};

};

//************************************************************************

// ChessBoard Class (Bottom white, Top black)

//************************************************************************

class ChessBoard{

public:

    // Data Members:

    Piece* board[8][8];

    // Member Functions

    void submitMove(char source_square[], char distination_square[]);
    void load_board(Piece* board[8][8]);

    // Constructor
    ChessBoard(){ load_board(board); };

};

#endif
