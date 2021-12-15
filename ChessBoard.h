#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include"piece.h"
#include<string>


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
    int user_king_pos[2];
    int opponent_king_pos[2];
    int threat_position[2];
    // position of piece that can block
    int blocking_piece_position[2];
    // position that blocks
    int blocking_position[2];
    int turn_count;

    // Member Functions

    bool wrong_turn( int start_row, int start_col, int turn_count );

    void print_board();
    void submitMove(std::string source_square_str, std::string destination_square_str);
    void convert_to_index(char source_square[3], char destination_square[3],
                          int source[2], int destination[2]);
    void load_board(Piece* board[8][8]);
    void resetBoard();

    bool adjacent_squares_check(int king_row, int king_col, int turn_count);
    bool can_king_move( int king_row, int king_col, int dest_row, int dest_col, int turn_count);
    bool valid_move(int start_row, int start_col, int dest_row, int dest_col);

    void insert_piece(int dest_row, int dest_col, char colour, char piece_type);
    void move_piece(int start_row, int start_col, int dest_row, int dest_col);

    bool check(int king_row, int king_col, int turn_count);
    bool can_block( int king_row, int king_col, int threat_row, int threat_col, int turn_count);
    bool can_block_space( int row, int col, int turn_count);
    bool check_mate( int king_row, int king_col, int turn_count);
    bool stalemate( int turn_count );

    std::string print_piece_type(char piece_type);
    std::string print_piece_colour(int turn_count);

    // Constructor
    // Change from loaed_test_board back
    ChessBoard()
        : B_king_pos{7, 7}, // change back to 0,4
            W_king_pos{0, 0}, // change back!
                user_king_pos{7,4},
                    opponent_king_pos{0,4},
                        threat_position{-1,-1},
                            blocking_piece_position{-1,-1},
                                blocking_position{-1,-1},
                                        turn_count(0)
    { load_board(board); };

    // Get Piece name is gonna be neccessary

};

#endif
