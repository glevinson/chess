#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include"piece.h"


// IN HEADER ONLY INCLUDE PIECE, SO ONLY INCLUDE PIECE
// WHEN OTHER PEOPLE USE YOUR LIBRARY, IF THEY USE THE HEADER ONLY & CONTAINS INCLUDES FOR EVEYTHING
// YOU NEEDED OVERALL. SLOWS DOWN COMPILATION FOR EVERYONE EVEN IF JUST USING YOUR HEADER FILE
// AND NOT NECCESSARILY MORE OF THE CODE

// HEADER FILE: ONLY INCLUDE HEADERS FOR CLASSES REFERRED TO IN HEADER
// IMPLEMENTATION: USE WHATEVER USED THERE
// EVERY CC FILE COMPILED SEPARATELY TO HEADER
// LINKING PHASE, SOURCE FILE FROM ONE BIT LINKED BACK TO OTHER FILES

// cpp files compiled, header files only compiled because they're in cpp files

// ************************************************************************

// ChessBoard Class (Bottom white, Top black)

// ************************************************************************

class ChessBoard{

public:

    // Data Members:

    Piece* board[8][8];
    int B_king_pos[2];
    int W_king_pos[2];

    // Member Functions

    void print_board();
    void submitMove(char source_square[], char distination_square[]);
    void convert_to_index(char source_square[3], char destination_square[3],
                          int source[2], int destination[2]);
    void load_board(Piece* board[8][8]);

    bool valid_move(int start_row, int start_col, int dest_row, int dest_col);

    // Delete out at the end !!!!
    void load_test_board(Piece* board[8][8]);

    bool check(int king_pos[2]);

    // Constructor
    // Change from loaed_test_board back
    ChessBoard()
        : B_king_pos{0, 4},
            W_king_pos{5, 7} // SHOULD BE 7,4
    { load_test_board(board); };

    // Get Piece name is gonna be neccessary

};

#endif
