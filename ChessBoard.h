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

// ****************************************************************************

// ChessBoard Class (Bottom white, Top black)

// ****************************************************************************

class ChessBoard{

private:

    Piece* board[8][8];
    // If turn_count = 0 it is white's turn, if turn_count = 1 it is Black's:
    int turn_count;
    // Player with turn's king position:
    int user_king_pos[2];
    // Player without turn's king position:
    int opponent_king_pos[2];
    // Position of piece that has a king in check:
    int threat_position[2];
    /* Position of piece that can block a piece putting current turn's
       King in check: */
    int blocking_piece_position[2];
    // Position that the blocking piece would move to:
    int blocking_position[2];

    // Loads beginning of match board setup:
    void load_board(Piece* board[8][8]);
    // Returns false if move White piece when Black's turn & vice-versa:
    bool wrong_turn( int start_row, int start_col, int turn_count );
    // Converts character board position to indices:
    void convert_to_index(char source_square[3], char destination_square[3],
                          int source[2], int destination[2]);
    // Returns true if the specified piece can move to the specified destination:
    bool valid_move(int start_row, int start_col, int dest_row, int dest_col);
    // Inserts the specified piece into the specified square:
    void insert_piece(int dest_row, int dest_col, char colour, char piece_type);
    // Moves piece at start square to destination square
    void move_piece(int start_row, int start_col, int dest_row, int dest_col);


    // Returns true if current turn's in stalemate
    bool stalemate( int turn_count );

// ****************************************************************************
// Check(-mate) functions
// ****************************************************************************

    // Returns true if current turn's King in check
    bool check(int king_row, int king_col, int turn_count);

    // Returns true if currents turn's King in check-mate
    bool check_mate( int king_row, int king_col, int turn_count);

    /* Returns true if specified King can move to specified square without 
       being in check: */
    bool can_king_move( int king_row, int king_col, int dest_row, int dest_col,
                        int turn_count);

    // Returns true if all specified Kings possible moves results in a check:
    bool adjacent_squares_check(int king_row, int king_col, int turn_count);

    /* Returns true if the threatening piece putting the specified King in 
       check can be blocked: */
    bool can_block( int king_row, int king_col, int threat_row, int threat_col,
                    int turn_count);

    // Returns true if a piece in the specified space would block check:
    bool can_block_space( int row, int col, int turn_count);

public:

    void submitMove(std::string source_square_str, 
                    std::string destination_square_str);
    void resetBoard();
    void alternate_turn_count(int turn_count);

// ****************************************************************************
// Getter Functions
// ****************************************************************************

    void print_board(); // DELETE @ end ! 
    std::string print_piece_type(char piece_type);
    std::string print_piece_colour(int turn_count);
    int get_turn_count() const;

    ChessBoard()
        :   turn_count(0),
                user_king_pos{7,4},
                    opponent_king_pos{0,4},
                        threat_position{-1,-1},
                            blocking_piece_position{-1,-1},
                                blocking_position{-1,-1}
    { load_board(board); };

};

#endif
