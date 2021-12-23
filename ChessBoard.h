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

private:

    // Data Members:

    Piece* board[8][8];
    // Black king position
    int B_king_pos[2];
    // White King Position
    int W_king_pos[2];
    // Player with turn's king position
    int user_king_pos[2];
    // Player without turn's king position
    int opponent_king_pos[2];
    // Position of piece that has a king in check 
    int threat_position[2];
    // Position of piece that can block a piece that puts their king in check
    int blocking_piece_position[2];
    // Position that the blocking piece will move to
    int blocking_position[2];
    // If turn_count = 0 it is white's turn, if turn_count = 1 it is Black's
    int turn_count;

    // Member Functions

    // Returns false if move White piece when Black's turn & vice-versa
    bool wrong_turn( int start_row, int start_col, int turn_count );

    // Converts character board position to indices
    void convert_to_index(char source_square[3], char destination_square[3],
                          int source[2], int destination[2]);
    
    void load_board(Piece* board[8][8]);

    bool adjacent_squares_check(int king_row, int king_col, int turn_count);
    bool can_king_move( int king_row, int king_col, int dest_row, int dest_col, int turn_count);
    bool valid_move(int start_row, int start_col, int dest_row, int dest_col);

    void insert_piece(int dest_row, int dest_col, char colour, char piece_type);
    void move_piece(int start_row, int start_col, int dest_row, int dest_col);

    // Returns 
    bool check(int king_row, int king_col, int turn_count);
    bool can_block( int king_row, int king_col, int threat_row, int threat_col, int turn_count);
    bool can_block_space( int row, int col, int turn_count);
    bool check_mate( int king_row, int king_col, int turn_count);
    bool stalemate( int turn_count );

public:

    void resetBoard();
    void submitMove(std::string source_square_str, std::string destination_square_str);
    void print_board();
    std::string print_piece_type(char piece_type);
    std::string print_piece_colour(int turn_count);
    int get_turn_count() const;
    void alternate_turn_count(int turn_count);

    // Constructor
    // Change from loaed_test_board back
    ChessBoard()
        : B_king_pos{0, 4},
            W_king_pos{7, 4},
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
