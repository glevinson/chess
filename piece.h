// #ifndef PIECE_H
// #define PIECE_H

// #include"ChessBoard.h"
// #include"pawn.h"
// #include"castle.h"
// #include"bishop.h"
// #include"knight.h"
// #include"king.h"
// #include"queen.h"

// //************************************************************************
// // Piece Class Header File
// //************************************************************************

// class Piece{

//   public:

//     // Data Mambers:

//     char colour;
//     char piece_type;

//     // Member Functions:

//     char get_colour() const;
//     char get_piece_type() const;
//     virtual bool possible_move(int start_col, int start_row, int dest_col, int dest_row) = 0;
//     virtual bool legal_move(int start_col, int start_row, int dest_col, int dest_row, Piece* board[8][8]) = 0;

//     bool legal_right(int start_col, int dest_col, int dest_row, Piece* board[8][8]);

//     // Constructor
//     Piece (char colour, char piece_type)
//       : colour(colour),
//           piece_type(piece_type){};
// };

// #endif